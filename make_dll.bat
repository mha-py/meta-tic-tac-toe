


c++ -c -o state.o state.cpp -Ofast
c++ -c -o dll.o dll.cpp -Ofast
c++ -c -o mcts_node.o mcts_node.cpp -Ofast
c++ -c -o mcts_tree.o mcts_tree.cpp -Ofast
c++ -o dll.dll -s -shared dll.o state.o mcts_tree.o mcts_node.o
