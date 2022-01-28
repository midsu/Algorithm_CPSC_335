# 335-project-3
> Clustering a Sensor network using NIC addresses

## Group members:

Ali Tahami: 📫 Atahami3@csu.fullerton.edu

Hamid Suha: 📫 hsuha@csu.fullerton.edu

Fall 2021

Instructors: Doina Bein (dbein@fullerton.edu)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Abstract:
In this project you will design and implement one algorithm related to hash tables that can aid various distributed algorithms to group sensors. Your project is about reading a fairly small number of distinct Network Interface Controllers (NICs), each being a 6-digit number in hexadecimal) and deciding which digit among the six gives the best balanced distribution of the NICs. 

The Hypothesis
This experiment will test the following hypotheses:

 - Different hash functions produce hash chains of various lengths when applied to the same dataset.
 - Hash tables offer a relatively fast way of storing and retrieving data.


For this problem, we will design:
- [x] addItem(): Given information about NIC number, create an Item object and insert into each of the six hash tables.  Note that each hash table has the product number as the key and an Item object as the value. To be completed.
- [x] removeItem(): Given product number, remove the corresponding NIC from each of the six hash tables. To be completed.
- [x] bestHashing(): The logic to calculate the balance for each of the six hash tables, and then identifying the hash table with the best balance should go into this method. Here, balance is defined as the difference between the sizes of the largest bucket and smallest bucket. Only check the first 10 buckets! (If the lowest balance factor is shared by more than one hash table, then return the first hash table with that lowest balance factor. For example, if both hT3 and hT7 have the lowest balance factor, then return the number 3. If hT2, hT4, and ht6 all share the lowest balance factor, then return the number 2.) Some hints on how to get the number of items in each bucket are included.  To be completed.
- [x] readTextfile(): The list of NIC numbers are in a text file. This method calls addItem() for each line. The code to read from the text file is already given. 


-------------------------------------------------------------------------------------------------------------------------------------------------------------------

## A description of the problem at hand is as follows:
Communication is paramount on sensor networks and it relies on grouping sensors into clusters, and providing code to be executed distributively at the sensors to maximize coverage and extend lifetime of the network, thus minimizing energy consumption for transmission. There are several types of sensors used to collect data from the environment; a simpiified classification is available at https://www.variohm.com/news-media/technical-blog-archive/types-of-sensors. A much detailed list is available here https://www.thomasnet.com/articles/instruments-controls/sensors/. 

For our problem, the following scenario motivates solving it. We are given a sensor network with a large number of MAC addresses, one for each sensor, and we would like to group the sensors to form a cluster of sensors based on their MAC address. We assume that the sensors are from the same manufacturer, so we consider only the NIC numbers are of importance for this problem. We assume that the MAC addresses are 6-digit numbers instead of 6-alphanumeric characters from the set {0..9, A..F}.

For example, let’s assume that we have the following NICs:
123456, 234567, 345678, 456789, 567890, 678901, 789012, 890123, 901234, 543210, 654321, 765432, 876543, 987654, 109876, 210987, 321098, 432109
If we choose storing the NIC numbers based on the first digit that we have:
- Cluster 0: no items
- Cluster 1: 123456, 109876
- Cluster 2: 234567, 210987
- Cluster 3: 345678, 321098
- Cluster 4: 456789, 432109
- Cluster 5: 567890
- Cluster 6: 678901
- Cluster 7: 789012
- Cluster 8: 890123
- Cluster 9: 901234, 987654

The difference in the clusters’ load is 2, for example between the load of Cluster 1 and Cluster 0.

- Cluster 0: 901234, 109876
- Cluster 1: 210987
- Cluster 2: 123456, 321098
- Cluster 3: 234567, 432109
- Cluster 4: 345678, 543210
- Cluster 5: 456789, 654321
- Cluster 6: 567890, 765432
- Cluster 7: 678901, 876543
- Cluster 8: 789012, 987654
- Cluster 9: 890123

The difference in the clusters’ load is 1 so clearly this is a more balanced organization of the NICs than the one based on the first digit.

One needs to compute six hash tables and select the first one which is the most balanced. For example, if hash table 1, 3 and 5 are the most balanced, then hash table 1 will be returned.

The first hash table organizes NICs based on the first digit, the second hash table has the hash function that organizes the NICs based on the second digit, etc. tha last hash table has the hash function that organizes the NICs based on the sixth (the last) digit.



END

