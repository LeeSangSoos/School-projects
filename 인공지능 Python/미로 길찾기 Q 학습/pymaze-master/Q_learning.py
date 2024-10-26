from __future__ import absolute_import
from src.maze_manager import MazeManager
from src.maze import Maze


if __name__ == "__main__":

    # The easiest way to use the library is through the Manager class. It acts as the glue between
    # The visualization, solver, and maze classes. Mazes inside the manager have unique ids that we use
    # to specify particular mazes.
    manager = MazeManager()

    # We can add mazes to the manager two different ways.
    # The first way, we specify the maze dimensions. The maze that is created gets returned back to you.
    maze = manager.add_maze(20, 20)

    manager.show_maze(maze.id)
    manager.set_filename("myFileName")
#############################################################################################  1
    
    manager.solve_maze(maze.id, "Q_learning", episodes=100000, a=0.9, r=0.9, e=0.4)

    manager.show_solution_animation(maze.id)
    
#############################################################################################  2
    
    manager.solve_maze(maze.id, "Q_learning", episodes=100000, a=0.7, r=0.7, e=0.4)

    manager.show_solution_animation(maze.id)
    
#############################################################################################  3
    
    manager.solve_maze(maze.id, "Q_learning", episodes=100000, a=0.5, r=0.5, e=0.4)

    manager.show_solution_animation(maze.id)
    
#############################################################################################  4

    manager.solve_maze(maze.id, "Q_learning", episodes=100000, a=0.3, r=0.3, e=0.4)

    manager.show_solution_animation(maze.id)
    