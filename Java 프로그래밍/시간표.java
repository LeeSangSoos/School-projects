package Lab_6pack;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Timetable {
	HashMap<String, String> SubjectList= new HashMap<>();
	HashMap<String, String> TimeSubjectList= new HashMap<>();
	Timetable() {
	}
	void ShowTables() {
		List<HashMap.Entry<String, String>> List2 = new ArrayList<HashMap.Entry<String, String>>(TimeSubjectList.entrySet());
		String a, b, c, d;
		List<HashMap.Entry<String, String>> temp = new ArrayList<HashMap.Entry<String, String>>(TimeSubjectList.entrySet());
		for(int i = 0; i < List2.size()-1; i++) {
			a=List2.get(i).getValue().substring(0,3);
			b=List2.get(i+1).getValue().substring(0,3);
			c=List2.get(i).getValue().substring(3,7);
			d=List2.get(i+1).getValue().substring(3,7);
			if(a.equals("TUE")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals("WED")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("TUE")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals("THU")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("TUE")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("WED")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals("FRI")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("TUE")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("WED")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("THU")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals("SAT")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("TUE")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("WED")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("THU")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("FRI")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals("SAT")) {
				if(b.equals("MON")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("TUE")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("WED")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("THU")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("FRI")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
				if(b.equals("SAT")) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
			if(a.equals(b)) {
				if(c.compareTo(d)==1) {
					temp.set(0, List2.get(i));
					List2.set(i, List2.get(i+1));
					List2.set(i+1, temp.get(0));
				}
			}
		}
		for(int i = 0; i < List2.size(); i++){
			System.out.println(List2.get(i).getKey()+" "+SubjectList.get(List2.get(i).getKey())+" "+List2.get(i).getValue());
	    }
	}
	String FindClassID(String class_name) {
		for (String key : SubjectList.keySet()) {
			String value=SubjectList.get(key);
			if(class_name.equals(value)) {
				return key;
			}
		}
		return "There is no value";
	}
	String FindClassName(String class_id) {
		return SubjectList.get(class_id);
	}
	void AddClass(String class_info) {
		String [] ready = new String[3];
		ready=class_info.split(" ");
		SubjectList.put(ready[0], ready[1]);
		TimeSubjectList.put(ready[0], ready[2]);
	}
}