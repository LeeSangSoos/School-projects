import matplotlib.pyplot as plt
import numpy as np

train_ori=open("train.csv","r")

#return reviews: [[5, ...], [1, ...] ...]
def pre_process(train_ori):
    train_data = open("train_data.txt", "w+")
    train_data2 = open("train_data2.txt", "w+")
    reviews={}
    
    # copy from original
    for line in train_ori:
        train_data.write(line)
    train_ori.close()

    # data to lower case
    train_data.seek(0)
    for line in train_data:
        b = line.lower()
        train_data2.write(b)
    train_data.close()
    open('train_data.txt', 'w').close()
    train_data = open('train_data.txt', 'w+')
    train_data2.seek(0)
    for line in train_data2.read():
        train_data.write(line)
    train_data2.close()
    open('train_data2.txt', 'w').close()
    train_data2 = open('train_data2.txt', 'w+')
    train_data.seek(0)

    # Remove special characters: ' ', !, ", #, $, %, &, ', (, ), *, +, , ,-, . ,/, :, ;, <, =, >, ?, @, [, ], \, ^, _, `, {, }, |, ~
    special_chars = ['!', '"', '#', '$', '%', '&', "'",
                     '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '\\', '^', '_', '`', '{', '}', '|', '~']
    for line in train_data:
        if len(line)>1:
            if line[1] == ',':
                if line[0]=='5': #change start of review to noticeable value
                    line = "GgOoDdSsTtAaRrTt" + line[1:]
                elif line[0]=='1':
                    line = "BbAaDdSsTtAaRrTt" + line[1:]
            for w in special_chars:
                line=line.replace(w, ' ')
            
        train_data2.write(line)
    train_data.close()
    open('train_data.txt', 'w').close()
    train_data = open('train_data.txt', 'w+')
    train_data2.seek(0)
    for line in train_data2.read():
        train_data.write(line)
    train_data2.close()
    open('train_data2.txt', 'w').close()
    train_data2 = open('train_data2.txt', 'w+')
    train_data.seek(0)

    # tokenize words
    comments = []
    onereview = []
    for line in train_data:
        line = line.split()
        if line and len(line) > 0:
            word = line[0]
            if word in ("GgOoDdSsTtAaRrTt", "BbAaDdSsTtAaRrTt") and len(onereview) != 0:
                addinglist = []
                addinglist = onereview.copy()
                comments.append(addinglist)
                onereview.clear()
            onereview.extend(line)
        else:
            continue

    comments.append(onereview)
    comments.pop(0)
    train_data.close()
    train_data2.close()

    # Remove stop words from stopwords.txt
    stopfile = open('stop words.txt', 'r')
    stop_words = stopfile.read().splitlines()
    stopfile.close()

    for word in stop_words:
        word = word.strip()

    reviews = []
    for line in comments:
        areview = []
        for word in line:
            word = word.strip()
            if word not in stop_words:
                areview.append(word)
        reviews.append(areview)
    return reviews

reviews=pre_process(train_ori)

# select 1000 frequent words from final
words_dic = {}
for line in reviews:
    for word in line:
        if word is line[0] and (word in ("GgOoDdSsTtAaRrTt", "BbAaDdSsTtAaRrTt")):
            continue
        else:
            if word in words_dic:
                words_dic[word] += 1
            else:
                words_dic[word] = words_dic.get(word, 0)+1
ranked_dic = sorted(words_dic.items(), key=lambda x: x[1], reverse=True)
dictionary = ranked_dic[:1000] #selected top 1000 words

#print 50 words from top
i=1
print("top 50 words: ")
for word, val in dictionary[:50]:
    print(i, end='')
    print(': '+word)
    i+=1
# --------------------------------------------------------------------------------------------------------------------------
# test data

dictionary2={}
dictionary2=dict(dictionary)
dictionary=dictionary2

def test_process(ratio_of_good_messages, ratio_of_bad_messages, good_ratio, bad_ratio):
    with open("test.csv", "r") as test_data:
        test_reviews = pre_process(test_data)
        for i in range(len(test_reviews)):
            line=test_reviews[i]
            temp = []
            for word in line:
                if (word in ("GgOoDdSsTtAaRrTt", "BbAaDdSsTtAaRrTt")):
                    temp.append(word)
                elif word in dictionary:
                    temp.append(word)
            test_reviews[i]=list(temp)
        
        right = 0
        wrong = 0
        answer = 0
        asumption = 0
        for line in test_reviews:
            good = 1 # evaluation value for good
            bad = 1  # evaluation value for bad
            good *= ratio_of_good_messages
            bad *= ratio_of_bad_messages
            if line[0] == "GgOoDdSsTtAaRrTt": # answer is good review
                answer = 5
            elif line[0] == "BbAaDdSsTtAaRrTt":  # answer is bad review
                answer = 1
            for word in line:
                if word is line[0] and (word in ("GgOoDdSsTtAaRrTt", "BbAaDdSsTtAaRrTt")):
                    pass
                else:
                    good *= good_ratio[word]
                    bad *= bad_ratio[word]
            if good >= bad:
                asumption = 5
            else:
                asumption = 1
            if answer == asumption:
                right += 1
            else:
                wrong += 1
                
    # for evaluation: accuracy:
    #(right good review + right bad review)/(all result=(right good + right bad + wrong good + wrong bad))
    result = right/(right+wrong)
    return result

def process(reviews):
    good_dict = {} #each frequency of words in good reviews (words in G)
    bad_dict = {} #each frequency of words in bad reviews (words in B)
    total_good_words = 0 # total freqeuncy of all words in good reviews (Wg)
    total_bad_words = 0 #total freqeuncy of all words in bad reviews (Wb)
    total_messages = 0 #total count of reviews (M)
    total_good_message = 0 #total count of good reivews (G)
    total_bad_message = 0 #total count of bad reviews (B)
    global dictionary

    # Laplace smoothing
    for word in dictionary:
        total_good_words += 1
        total_bad_words += 1
        good_dict[word] = 1
        bad_dict[word] = 1

    # ratio of each word in each message
    good_ratio = {}  # p(word)|G
    bad_ratio = {} # p(word)|B
    
    # get good and bad reviews
    for line in reviews:
        total_messages += 1 # total messages +1
        if line[0] == "GgOoDdSsTtAaRrTt":
            total_good_message += 1 # total good messages +1
            for word in line[1:]:
                if word in dictionary:
                    total_good_words += 1 # total frequency of words in good review +1
                    good_dict[word] += 1 # frequency of certain word in good review +1
        elif line[0] == "BbAaDdSsTtAaRrTt":
            total_bad_message += 1 # total bad messages +1
            for word in line[1:]:
                if word in dictionary:
                    total_bad_words += 1  # total frequency of words in bad review +1
                    bad_dict[word] += 1 # frequency of certain word in bad review +1

    #set ratio of two kinds of messages
    # p(B)=(B)/(M)
    ratio_of_good_messages = total_good_message/total_messages
    # p(G)=(G)/(M)
    ratio_of_bad_messages = total_bad_message/total_messages
    
    #set ratio of each word
    for word in dictionary:
        good_ratio.setdefault(word, 0)
        bad_ratio.setdefault(word, 0)
        good_ratio[word] = good_dict[word]/total_good_words  # p(w | G)
        bad_ratio[word] = bad_dict[word]/total_bad_words  # p(w | B)

    result=test_process(ratio_of_good_messages,
                       ratio_of_bad_messages, good_ratio, bad_ratio)
    return result


#print("400")
result_10=process(reviews[:int(len(reviews)*10/100)])
#print("1200")
result_30=process(reviews[:int(len(reviews)*30/100)])
#print("2000")
result_50=process(reviews[:int(len(reviews)*50/100)])
#print("2800")
result_70=process(reviews[:int(len(reviews)*70/100)])
#print("4000")
result_100=process(reviews[:int(len(reviews))])

print(result_10*100,end="%\n")
print(result_30*100, end="%\n")
print(result_50*100, end="%\n")
print(result_70*100, end="%\n")
print(result_100*100,end="%\n")

ypoints = np.array([result_10*100, result_30*100,
                   result_50*100, result_70*100, result_100*100])
xpoints=np.array([400, 1200, 2000, 2800, 4000])

plt.plot(xpoints, ypoints, linestyle='dotted')

plt.show()
'''
Laplace smoothing:
    for every word in dictionary:
        good_dict[word]+=1
        bad_dict[word]+=1 
        total_good_words+=1
        total_bad_words+=1
        
    for word,val in dictionary:
        if word in good_dict:
            good_ratio[word]=good_dict[word]/total_good_words
        if word in bad_dict:
            bad_ratio[word] = bad_dict[word]/total_bad_words
        
Estimation:
    for given review from test:
        get words(in dictionary):
            p(good|words)= (good_dict[word1]*good_dict[word2]*good_dict[word3]...)*ratio_of_good_messages
        
    add test data (words from review) to good_dict, bad_dict and
    recalculate good_ratio, bad_ratio
    
    add review to total_good_messages, total_bad_messages, total_messages
    recalculate ratio_of_good_messages, ratio_of_bad_messages
    
    
Learning curve:
    initial data=0
    start ratio = every word appeared 1
    start from first review of train.csv?
    train one review->test
    train one review->test
    train one review->test?
    
for evaluation: accuracy:
    (맞춘 good review + 맞춘 bad review)/(총 리뷰 개수(맞춘 good + 맞춘 bad + 틀린 good + 틀린 bad))
'''