import time
import random
import logging
from src.maze import Maze
import math
import random
DOWN, RIGHT, UP, LEFT =0, 1, 2, 3

logging.basicConfig(level=logging.DEBUG)


class Solver(object):
	"""Base class for solution methods.
	Every new solution method should override the solve method.

	Attributes:
		maze (list): The maze which is being solved.
		neighbor_method:
		quiet_mode: When enabled, information is not outputted to the console

	"""

	def __init__(self, maze, quiet_mode, neighbor_method):
		logging.debug("Class Solver ctor called")

		self.maze = maze
		self.neighbor_method = neighbor_method
		self.name = ""
		self.quiet_mode = quiet_mode

	def solve(self):
		logging.debug('Class: Solver solve called')
		raise NotImplementedError

	def get_name(self):
		logging.debug('Class Solver get_name called')
		raise self.name

	def get_path(self):
		logging.debug('Class Solver get_path called')
		return self.path

class BreadthFirst(Solver):

	def __init__(self, maze, quiet_mode=False, neighbor_method="brute-force"):
		logging.debug('Class BreadthFirst ctor called')

		self.name = "Breadth First Recursive"
		super().__init__(maze, neighbor_method, quiet_mode)

	def solve(self):

		"""Function that implements the breadth-first algorithm for solving the maze. This means that
				for each iteration in the outer loop, the search visits one cell in all possible branches. Then
				moves on to the next level of cells in each branch to continue the search."""

		logging.debug("Class BreadthFirst solve called")
		current_level = [self.maze.entry_coor]  # Stack of cells at current level of search
		path = list()  # To track path of solution cell coordinates

		print("\nSolving the maze with breadth-first search...")
		time_start = time.time()

		while True:  # Loop until return statement is encountered
			next_level = list()

			while current_level:  # While still cells left to search on current level
				k_curr, l_curr = current_level.pop(0)  # Search one cell on the current level
				self.maze.grid[k_curr][l_curr].visited = True  # Mark current cell as visited
				path.append(((k_curr, l_curr), False))  # Append current cell to total search path

				if (k_curr, l_curr) == self.maze.exit_coor:  # Exit if current cell is exit cell
					if not self.quiet_mode:
						print("Number of moves performed: {}".format(len(path)))
						print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))
					return path

				neighbour_coors = self.maze.find_neighbours(k_curr, l_curr)  # Find neighbour indicies
				neighbour_coors = self.maze.validate_neighbours_solve(neighbour_coors, k_curr,
																  l_curr, self.maze.exit_coor[0],
																  self.maze.exit_coor[1], self.neighbor_method)

				if neighbour_coors is not None:
					for coor in neighbour_coors:
						next_level.append(coor)  # Add all existing real neighbours to next search level

			for cell in next_level:
				current_level.append(cell)  # Update current_level list with cells for nex search level
		logging.debug("Class BreadthFirst leaving solve")

class BiDirectional(Solver):

	def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
		logging.debug('Class BiDirectional ctor called')

		super().__init__(maze, neighbor_method, quiet_mode)
		self.name = "Bi Directional"

	def solve(self):

		"""Function that implements a bidirectional depth-first recursive backtracker algorithm for
		solving the maze, i.e. starting at the entry point and exit points where each search searches
		for the other search path. NOTE: THE FUNCTION ENDS IN AN INFINITE LOOP FOR SOME RARE CASES OF
		THE INPUT MAZE. WILL BE FIXED IN FUTURE."""
		logging.debug("Class BiDirectional solve called")

		grid = self.maze.grid
		k_curr, l_curr = self.maze.entry_coor            # Where to start the first search
		p_curr, q_curr = self.maze.exit_coor             # Where to start the second search
		grid[k_curr][l_curr].visited = True    # Set initial cell to visited
		grid[p_curr][q_curr].visited = True    # Set final cell to visited
		backtrack_kl = list()                  # Stack of visited cells for backtracking
		backtrack_pq = list()                  # Stack of visited cells for backtracking
		path_kl = list()                       # To track path of solution and backtracking cells
		path_pq = list()                       # To track path of solution and backtracking cells

		if not self.quiet_mode:
			print("\nSolving the maze with bidirectional depth-first search...")
		time_start = time.clock()

		while True:   # Loop until return statement is encountered
			neighbours_kl = self.maze.find_neighbours(k_curr, l_curr)    # Find neighbours for first search
			real_neighbours_kl = [neigh for neigh in neighbours_kl if not grid[k_curr][l_curr].is_walls_between(grid[neigh[0]][neigh[1]])]
			neighbours_kl = [neigh for neigh in real_neighbours_kl if not grid[neigh[0]][neigh[1]].visited]

			neighbours_pq = self.maze.find_neighbours(p_curr, q_curr)    # Find neighbours for second search
			real_neighbours_pq = [neigh for neigh in neighbours_pq if not grid[p_curr][q_curr].is_walls_between(grid[neigh[0]][neigh[1]])]
			neighbours_pq = [neigh for neigh in real_neighbours_pq if not grid[neigh[0]][neigh[1]].visited]

			if len(neighbours_kl) > 0:   # If there are unvisited neighbour cells
				backtrack_kl.append((k_curr, l_curr))              # Add current cell to stack
				path_kl.append(((k_curr, l_curr), False))          # Add coordinates to part of search path
				k_next, l_next = random.choice(neighbours_kl)      # Choose random neighbour
				grid[k_next][l_next].visited = True                # Move to that neighbour
				k_curr = k_next
				l_curr = l_next

			elif len(backtrack_kl) > 0:                  # If there are no unvisited neighbour cells
				path_kl.append(((k_curr, l_curr), True))   # Add coordinates to part of search path
				k_curr, l_curr = backtrack_kl.pop()        # Pop previous visited cell (backtracking)

			if len(neighbours_pq) > 0:                        # If there are unvisited neighbour cells
				backtrack_pq.append((p_curr, q_curr))           # Add current cell to stack
				path_pq.append(((p_curr, q_curr), False))       # Add coordinates to part of search path
				p_next, q_next = random.choice(neighbours_pq)   # Choose random neighbour
				grid[p_next][q_next].visited = True             # Move to that neighbour
				p_curr = p_next
				q_curr = q_next

			elif len(backtrack_pq) > 0:                  # If there are no unvisited neighbour cells
				path_pq.append(((p_curr, q_curr), True))   # Add coordinates to part of search path
				p_curr, q_curr = backtrack_pq.pop()        # Pop previous visited cell (backtracking)

			# Exit loop and return path if any opf the kl neighbours are in path_pq.
			if any((True for n_kl in real_neighbours_kl if (n_kl, False) in path_pq)):
				path_kl.append(((k_curr, l_curr), False))
				path = [p_el for p_tuple in zip(path_kl, path_pq) for p_el in p_tuple]  # Zip paths
				if not self.quiet_mode:
					print("Number of moves performed: {}".format(len(path)))
					print("Execution time for algorithm: {:.4f}".format(time.clock() - time_start))
				logging.debug("Class BiDirectional leaving solve")
				return path

			# Exit loop and return path if any opf the pq neighbours are in path_kl.
			elif any((True for n_pq in real_neighbours_pq if (n_pq, False) in path_kl)):
				path_pq.append(((p_curr, q_curr), False))
				path = [p_el for p_tuple in zip(path_kl, path_pq) for p_el in p_tuple]  # Zip paths
				if not self.quiet_mode:
					print("Number of moves performed: {}".format(len(path)))
					print("Execution time for algorithm: {:.4f}".format(time.clock() - time_start))
				logging.debug("Class BiDirectional leaving solve")
				return path

class DepthFirstBacktracker(Solver):
	"""A solver that implements the depth-first recursive backtracker algorithm.
	"""

	def __init__(self, maze, quiet_mode=False,  neighbor_method="fancy"):
		logging.debug('Class DepthFirstBacktracker ctor called')

		super().__init__(maze, neighbor_method, quiet_mode)
		self.name = "Depth First Backtracker"

	def solve(self):
		logging.debug("Class DepthFirstBacktracker solve called")
		k_curr, l_curr = self.maze.entry_coor      # Where to start searching
		self.maze.grid[k_curr][l_curr].visited = True     # Set initial cell to visited
		visited_cells = list()                  # Stack of visited cells for backtracking
		path = list()                           # To track path of solution and backtracking cells
		if not self.quiet_mode:
			print("\nSolving the maze with depth-first search...")

		time_start = time.time()

		while (k_curr, l_curr) != self.maze.exit_coor:     # While the exit cell has not been encountered
			neighbour_indices = self.maze.find_neighbours(k_curr, l_curr)    # Find neighbour indices
			neighbour_indices = self.maze.validate_neighbours_solve(neighbour_indices, k_curr,
				l_curr, self.maze.exit_coor[0], self.maze.exit_coor[1], self.neighbor_method)

			if neighbour_indices is not None:   # If there are unvisited neighbour cells
				visited_cells.append((k_curr, l_curr))              # Add current cell to stack
				path.append(((k_curr, l_curr), False))  # Add coordinates to part of search path
				k_next, l_next = random.choice(neighbour_indices)   # Choose random neighbour
				self.maze.grid[k_next][l_next].visited = True                 # Move to that neighbour
				k_curr = k_next
				l_curr = l_next

			elif len(visited_cells) > 0:              # If there are no unvisited neighbour cells
				path.append(((k_curr, l_curr), True))   # Add coordinates to part of search path
				k_curr, l_curr = visited_cells.pop()    # Pop previous visited cell (backtracking)

		path.append(((k_curr, l_curr), False))  # Append final location to path
		if not self.quiet_mode:
			print("Number of moves performed: {}".format(len(path)))
			print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

		logging.debug('Class DepthFirstBacktracker leaving solve')
		return path
	
class UCS2(Solver):
	def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
		logging.debug('Class UCS2 ctor called')
		self.name = "UCS2"
		super().__init__(maze, neighbor_method, quiet_mode)
	def uniform_cost_search(self, maze):
		logging.debug("Class UCS2 solve called")
		r1,c1=maze.entry_coor
		current_level = [(r1,c1,0)]  # Stack of cells at current level of search
		path = list()  # To track path of solution cell coordinates
		print("\nSolving the maze with UCS2 search...")
		curr_pos=(r1,c1)
		while True:  # Loop until return statement is encountered
			while current_level:  # While still cells left to search on current level
				obj=(0,0,10000)
				objx=-1
				for cor in current_level:
					if(obj[2]>cor[2]):
						obj=cor
						objx=current_level.index(obj)
				k_curr, l_curr, c_curr = current_level.pop(objx) # Search one cell on the current level
				#---------------------------------------------------------------------------------------------------
				#back track
				if(len(path)>1):
					kc=k_curr; lc=l_curr; cost=c_curr
					kc2, lc2, cost2=path[-1]
					if((abs(kc-kc2)>1 or abs(lc-lc2)>1 or (abs(lc-lc2)==1 and abs(kc-kc2)==1)) or 
						maze.grid[kc][lc].is_walls_between(maze.grid[kc2][lc2])):
						path_come=list()
						path_temp=list()
						while(cost2>0):
							for i in path:
								if((((i[0]-kc2==1 or i[0]-kc2==-1) and i[1]==lc2) or ((i[1]-lc2==1 or i[1]-lc2==-1) and i[0]==kc2)) and (cost2==i[2]+1)
	  								and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc2][lc2])):
									kc2, lc2, cost2=i
									path_temp.append((kc2,lc2,cost2))
						while(cost>0):
							for i in path:
								if((((i[0]-kc==1 or i[0]-kc==-1) and i[1]==lc) or ((i[1]-lc==1 or i[1]-lc==-1) and i[0]==kc)) and (cost==i[2]+1)
	  							and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc][lc])):
									kc, lc, cost=i
									path_come.append((kc,lc,cost))
									for j in path_temp:
										if((kc,lc)==(j[0],j[1])):
											path_come=path_come[::-1]
											path_come.pop(0)
											path_temp = [item for item in path_temp if item[2] >= j[2]]
											path.extend(path_temp)
											path.extend(path_come)
											cost=0
											break
								if(cost==0):
									break
				#----------------------------------------------------------------------------------------------------
				maze.grid[k_curr][l_curr].visited = True  # Mark current cell as visited
				path.append((k_curr, l_curr, c_curr))  # Append current cell to total search path

				if (k_curr, l_curr) == maze.exit_coor:  # Exit if current cell is exit cell
					if not self.quiet_mode:
						print("Number of moves performed: {}".format(len(path)))
					path_len=c_curr
					opt_path=[(0,0) for i in range(path_len+1)]
					kc=k_curr; lc=l_curr
					opt_path[path_len]=((kc,lc),False)
					path_len-=1
					while(path_len>-1):
						for i in path:
							if((((i[0]-kc==1 or i[0]-kc==-1) and i[1]==lc) or ((i[1]-lc==1 or i[1]-lc==-1) and i[0]==kc)) and (path_len==i[2])
	  							and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc][lc])):
								opt_path[i[2]]=((i[0],i[1]),False)
								kc=i[0]
								lc=i[1]
								path_len-=1
					#-------------------------------------------------------------------------------------------------
					opt_path.clear()
					for i in path:
						opt_path.append(((i[0],i[1]),False))
					return (opt_path, len(path))
					#-------------------------------------------------------------------------------------------------
				neighbour_coors = maze.find_neighbours3(k_curr, l_curr, c_curr)  # Find neighbour indicies
				if neighbour_coors is not None:
					for coor in neighbour_coors:
						current_level.append(coor)  # Add all existing real neighbours to next search level
		logging.debug("Class UCS2 leaving solve")

class A_search(Solver):
	def __init__(self, maze, quiet_mode=False, neighbor_method="fancy"):
		logging.debug('Class A_search ctor called')
		self.name = "A_search"
		super().__init__(maze, neighbor_method, quiet_mode)
	def a_star_search(self, maze, h):
		logging.debug("Class A_search solve called")
		r1,c1=maze.entry_coor
		current_level = [(r1,c1,0)]  # Stack of cells at current level of search
		path = list()  # To track path of solution cell coordinates
		print("\nSolving the maze with A_search search...")
		curr_pos=(r1,c1)

		dest=maze.exit_coor

		while True:  # Loop until return statement is encountered
			while current_level:  # While still cells left to search on current level
				obj=current_level[0]
				obj_cost2=10000
				objx=0
				for cor in current_level:
					cost2=h(cor[0],cor[1],dest[0],dest[1])
					if((obj[2]+obj_cost2)>(cor[2]+cost2)):
						obj=cor
						obj_cost2=cost2
						objx=current_level.index(obj)
				k_curr, l_curr, c_curr = current_level.pop(objx) # Search one cell on the current level
				#---------------------------------------------------------------------------------------------------
				#back track
				if(len(path)>1):
					kc=k_curr; lc=l_curr; cost=c_curr
					kc2, lc2, cost2=path[-1]
					if((abs(kc-kc2)>1 or abs(lc-lc2)>1 or (abs(lc-lc2)==1 and abs(kc-kc2)==1)) or 
						maze.grid[kc][lc].is_walls_between(maze.grid[kc2][lc2])):
						path_come=list()
						path_temp=list()
						while(cost2>0):
							for i in path:
								if((((i[0]-kc2==1 or i[0]-kc2==-1) and i[1]==lc2) or ((i[1]-lc2==1 or i[1]-lc2==-1) and i[0]==kc2)) and (cost2==i[2]+1)
	  								and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc2][lc2])):
									kc2, lc2, cost2=i
									path_temp.append((kc2,lc2,cost2))
						while(cost>0):
							for i in path:
								if((((i[0]-kc==1 or i[0]-kc==-1) and i[1]==lc) or ((i[1]-lc==1 or i[1]-lc==-1) and i[0]==kc)) and (cost==i[2]+1)
	  							and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc][lc])):
									kc, lc, cost=i
									path_come.append((kc,lc,cost))
									for j in path_temp:
										if((kc,lc)==(j[0],j[1])):
											path_come=path_come[::-1]
											path_come.pop(0)
											path_temp = [item for item in path_temp if item[2] >= j[2]]
											path.extend(path_temp)
											path.extend(path_come)
											cost=0
											break
								if(cost==0):
									break
				#----------------------------------------------------------------------------------------------------
				maze.grid[k_curr][l_curr].visited = True  # Mark current cell as visited
				path.append((k_curr, l_curr, c_curr))  # Append current cell to total search path

				if (k_curr, l_curr) == maze.exit_coor:  # Exit if current cell is exit cell
					if not self.quiet_mode:
						print("Number of moves performed: {}".format(len(path)))
					path_len=c_curr
					opt_path=[(0,0) for i in range(path_len+1)]
					kc=k_curr; lc=l_curr
					opt_path[path_len]=((kc,lc),False)
					path_len-=1
					while(path_len>-1):
						for i in path:
							if((((i[0]-kc==1 or i[0]-kc==-1) and i[1]==lc) or ((i[1]-lc==1 or i[1]-lc==-1) and i[0]==kc)) and (path_len==i[2])
	  							and not maze.grid[i[0]][i[1]].is_walls_between(maze.grid[kc][lc])):
								opt_path[i[2]]=((i[0],i[1]),False)
								kc=i[0]
								lc=i[1]
								path_len-=1
					#-------------------------------------------------------------------------------------------------
					opt_path.clear()
					for i in path:
						opt_path.append(((i[0],i[1]),False))
					return (opt_path, len(path))
					#-------------------------------------------------------------------------------------------------
				neighbour_coors = maze.find_neighbours3(k_curr, l_curr, c_curr)  # Find neighbour indicies
				if neighbour_coors is not None:
					for coor in neighbour_coors:
						current_level.append(coor)  # Add all existing real neighbours to next search level
		logging.debug("Class UCS2 leaving solve")

def get_max_action(list, k_curr, l_curr, neighbour_indices):
	action=0
	max=-1000
	if neighbour_indices is not None:
		for i in range(0,4):
			if list[i]>max:
				if i == 0:
					if (k_curr-1, l_curr) in neighbour_indices:
						max=list[i]
						action=i
				elif i==1:
					if (k_curr, l_curr+1) in neighbour_indices:
						max=list[i]
						action=i
				elif i==2:
					if (k_curr+1, l_curr) in neighbour_indices:
						max=list[i]
						action=i
				elif i==3:
					if (k_curr, l_curr-1) in neighbour_indices:
						max=list[i]
						action=i
			elif list[i]==max:
				k=random.randrange(0,10)
				if k<5:
					if i == 0:
						if (k_curr-1, l_curr) in neighbour_indices:
							max=list[i]
							action=i
					elif i==1:
						if (k_curr, l_curr+1) in neighbour_indices:
							max=list[i]
							action=i
					elif i==2:
						if (k_curr+1, l_curr) in neighbour_indices:
							max=list[i]
							action=i
					elif i==3:
						if (k_curr, l_curr-1) in neighbour_indices:
							max=list[i]
							action=i
	return action

def get_max_reward(list,k_curr, l_curr, neighbour_indices):
	max=-1000
	if neighbour_indices is not None:
		for i in range(0,4):
			if list[i]>max:
				if i == 0:
					if (k_curr-1, l_curr) in neighbour_indices:
						max=list[i]
				elif i==1:
					if (k_curr, l_curr+1) in neighbour_indices:
						max=list[i]
				elif i==2:
					if (k_curr+1, l_curr) in neighbour_indices:
						max=list[i]
				elif i==3:
					if (k_curr, l_curr-1) in neighbour_indices:
						max=list[i]

	return max

def get_reward(k_curr, l_curr, k_next, l_next, maze):
		#neighbour_indices = maze.find_neighbours(k_next, l_next)
		#elif neighbour_indices is not None:
		#	if len(neighbour_indices)==1:
		#		reward=-1000
		reward=0
		if maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_next][l_next]):
			reward=-1
		elif (k_next,l_next)==maze.exit_coor:
			reward=100
		else:
			reward=-0.1
		return reward

def q_learning(maze, episodes, a, r, e):# a: learning factor, r: decrease fac, e: explore_exploit fac
	row_max=maze.num_rows
	col_max=maze.num_cols
	q_table=[[0 for i in range(4)] for j in range(row_max*col_max)]
	total_iter=0
	for i in range(episodes):
		if i%2000==0:
			print(f"{i} episode(s) done")
		k_curr, l_curr = maze.entry_coor      # Where to start searching
		iteration_limit=30000
		if i<10:
			iteration_limit=100000
		iteration=0
		while (k_curr, l_curr) != maze.exit_coor and iteration <= iteration_limit:     # While the exit cell has not been encountered
			neighbour_indices = maze.find_neighbours(k_curr, l_curr)    # Find neighbour indices
			iteration=iteration+1
			total_iter+=1

			if neighbour_indices is not None:
				move=False
				while (not move):
					e_decide=random.random()

					if e_decide>e:
						action=get_max_action(q_table[k_curr*row_max+l_curr*1], k_curr, l_curr, neighbour_indices)
					else:
						action=random.randrange(0,3)

					if action == DOWN and k_curr-1 >= 0:
						neighbour_indices2= maze.find_neighbours(k_curr-1, l_curr)
						reward=get_reward(k_curr, l_curr, k_curr-1, l_curr, maze)

						if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr-1][l_curr]) :
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward +r*get_max_reward(q_table[(k_curr-1)*row_max+l_curr*1], k_curr-1, l_curr,neighbour_indices2)-q_table[k_curr*row_max+l_curr*1][action])
							k_curr-=1
							move=True
						else:
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward-q_table[k_curr*row_max+l_curr*1][action])
					elif action == RIGHT and l_curr+1 < maze.num_cols:
						neighbour_indices2= maze.find_neighbours(k_curr, l_curr+1)
						reward=get_reward(k_curr, l_curr, k_curr, l_curr+1, maze)
						
						if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr][l_curr+1]) :
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward+r*get_max_reward(q_table[(k_curr)*row_max+(l_curr+1)*1], k_curr, l_curr+1,neighbour_indices2)-q_table[k_curr*row_max+l_curr*1][action])
							l_curr+=1
							move=True
						else:
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward-q_table[k_curr*row_max+l_curr*1][action])
					elif action == UP and k_curr+1 < maze.num_rows:
						neighbour_indices2= maze.find_neighbours(k_curr+1, l_curr)
						reward=get_reward(k_curr, l_curr, k_curr+1, l_curr, maze)
						
						if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr+1][l_curr]) :
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward+r*get_max_reward(q_table[(k_curr+1)*row_max+(l_curr)*1],k_curr+1, l_curr, neighbour_indices2)-q_table[k_curr*row_max+l_curr*1][action])
							k_curr+=1
							move=True
						else:
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward-q_table[k_curr*row_max+l_curr*1][action])
					elif action == LEFT and l_curr-1 >= 0:
						neighbour_indices2= maze.find_neighbours(k_curr, l_curr-1)
						reward=get_reward(k_curr, l_curr, k_curr, l_curr-1, maze)
						
						if not maze.grid[k_curr][l_curr].is_walls_between(maze.grid[k_curr][l_curr-1]) :
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward+r*get_max_reward(q_table[(k_curr)*row_max+(l_curr-1)*1], k_curr, l_curr-1,neighbour_indices2)-q_table[k_curr*row_max+l_curr*1][action])
							l_curr-=1
							move=True
						else:
							q_table[k_curr*row_max+l_curr*1][action]=q_table[k_curr*row_max+l_curr*1][action]+a*(reward-q_table[k_curr*row_max+l_curr*1][action])

	'''
	for i in range(len(q_table)):
		for j in range(len(q_table[i])):
			q_table[i][j] = round(q_table[i][j], 7)
	print(f"(a={a}, r={r}), total iteration: {total_iter}")
	'''
	f = open("test.txt", "a")
	f.write(f"(a={a}, r={r}), total iteration: {total_iter}")
	f.close()
	return q_table

class Q_learning(Solver):
	"""A solver that implements the Q_learning algorithm.
	"""
	def __init__(self, maze, quiet_mode=False,  neighbor_method="fancy", episodes=100, a=0.1, r=0.1, e=0.5):
		logging.debug('Class Q_learning ctor called')

		super().__init__(maze, neighbor_method, quiet_mode)
		self.name = "Q_learning"
		self.episodes=episodes
		self.a=a
		self.r=r
		self.e=e
	
	def solve(self):
		logging.debug("Class Q_learning solve called")
		k_curr, l_curr = self.maze.entry_coor      # Where to start searching
		self.maze.grid[k_curr][l_curr].visited = True     # Set initial cell to visited
		path = list()                           # To track path of solution and backtracking cells
		if not self.quiet_mode:
			print("\nSolving the maze with Q_learning search...")
		row_max=self.maze.num_rows
		col_max=self.maze.num_cols
		time_start = time.time()
		q_table=q_learning(self.maze,self.episodes,self.a,self.r, self.e)
		iteration_limit=10000
		iteration=0
		print("path searching start")
		k_old=-1;l_old=-1;k_new=0;l_new=0
		visited=[0 for j in range(row_max*col_max)]
		while (k_curr, l_curr) != self.maze.exit_coor and iteration <= iteration_limit:     # While the exit cell has not been encountered
			iteration+=1
			move=False
				
			neighbour_indices = self.maze.find_neighbours(k_curr, l_curr)    # Find neighbour indices
			row_max=self.maze.num_rows
			col_max=self.maze.num_cols
			while (not move):
				action=get_max_action(q_table[k_curr*row_max+l_curr*1], k_curr, l_curr,neighbour_indices)

				if action == 0 and k_curr-1 >= 0:
					if not self.maze.grid[k_curr][l_curr].is_walls_between(self.maze.grid[k_curr-1][l_curr]) :
						k_new=k_curr-1
						l_new=l_curr
						move=True

				elif action == 1 and l_curr+1 < self.maze.num_cols:
					if not self.maze.grid[k_curr][l_curr].is_walls_between(self.maze.grid[k_curr][l_curr+1]) :
						k_new=k_curr
						l_new=l_curr+1
						move=True

				elif action == 2 and k_curr+1 < self.maze.num_rows:
					if not self.maze.grid[k_curr][l_curr].is_walls_between(self.maze.grid[k_curr+1][l_curr]) :
						k_new=k_curr+1
						l_new=l_curr
						move=True

				elif action == 3 and l_curr-1 >= 0:
					if not self.maze.grid[k_curr][l_curr].is_walls_between(self.maze.grid[k_curr][l_curr-1]) :
						k_new=k_curr
						l_new=l_curr-1
						move=True
			
			if visited[k_curr*row_max+l_curr*1] == 1 and (k_curr, l_curr)!= self.maze.entry_coor:
				path.append(((k_curr, l_curr), True))
				visited[k_curr*row_max+l_curr*1] = 0
			elif (k_old, l_old)==(k_new, l_new) and (k_curr, l_curr)!= self.maze.entry_coor:
				path.append(((k_curr, l_curr), True))
				visited[k_curr*row_max+l_curr*1] = 0
			else:
				path.append(((k_curr, l_curr), False))
				visited[k_curr*row_max+l_curr*1] = 1
			'''
			if neighbour_indices is not None:   # If there are unvisited neighbour cells
				if (k_old, l_old)==(k_new, l_new) and (k_curr, l_curr)!= self.maze.entry_coor:
					path.append(((k_curr, l_curr), True))  # Add coordinates to part of search path
				else:
					visited.append((k_curr, l_curr))              # Add current cell to stack
					path.append(((k_curr, l_curr), False))  # Add coordinates to part of search path
					self.maze.grid[k_curr][l_curr].visited = True
			elif len(visited) > 0:              # If there are no unvisited neighbour cells
				path.append(((k_curr, l_curr), True))   # Add coordinates to part of search path
				k_pre, l_pre=visited.pop()    # Pop previous visited cell (backtracking)
				self.maze.grid[k_pre][l_pre].visited = False
			'''

			k_old=k_curr
			l_old=l_curr
			k_curr=k_new
			l_curr=l_new


		path.append(((k_curr, l_curr), False))  # Append final location to path

		print("finish path searching")
		if not self.quiet_mode:
			print("Number of moves performed: {}".format(len(path)))
			print("Execution time for algorithm: {:.4f}".format(time.time() - time_start))

		logging.debug('Class Q_learning leaving solve')
		return path