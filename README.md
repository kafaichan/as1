=> FOLDER STRUCTURE
1. data folder save the networks graph data
2. query folder save each network query, each file contains 100 pseudo-randomized generated queries(srand(1)).
3. dijkstra algorithm in dijkstra folder
4. pruned landmark labelling algorithm in pll folder


=> Dijkstra Folder
In order to run a specific network, you need to do:
   (1) edit main.cpp, #define roadnet/bike/test to use the relative network data
   (2) edit dijkstra.cpp, #define one of them: roadnet/bike/test 
   (3) if you use stl library, #define stl in dijkstra.cpp, #define stl in heap.h
   
   (4) if you use boost library:   
      (a) #define boostfib or #define boostpq to use boost fibonacci heap and boost 
          priority queue respectively in dijkstra.cpp

      (b)#define boosttest in heap.h  
      
      (c)uncomment the #include lines in dijkstra.h
      
      (d)add -I XX/boost_1_62_0(YOUR BOOST library root folder path) options to Makefile dijkstra.o


=> pll Folder
    (1) edit main.cpp, #define roadnet/bike/test to use the relative network data
    (2) edit pll.cpp, #define one of them: roadnet/bike/test
    (3) if you use boost library,
        (a) #define boosttest in pll.cpp
        (b) uncomment the #include lines in pll.cpp, currently only support fibonacci heap, you can reference the dijkstra.cpp to edit the code in            order to use boost priority queue
        (c) #define boosttest in heap.h

    (4)same as Dijkstra 4(d) part 
