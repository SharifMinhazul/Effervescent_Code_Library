bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_first()<<endl; // prints 1
bs._Find_next(idx). This function returns first set bit after index idx.for example:

bitset<17>BS;
BS[1] = BS[7] = 1;
cout<<BS._Find_next(1)<<','<<BS._Find_next(3)<<endl; // prints 7,7
So this code will print all of the set bits of BS:

for(int i=BS._Find_first();i< BS.size();i = BS._Find_next(i))
    cout<<i<<endl;
//Note that there isn't any set bit after idx, BS._Find_next(idx) will return BS.size(); same as calling BS._Find_first() when bitset is clear;
