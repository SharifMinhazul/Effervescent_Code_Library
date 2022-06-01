ll SOD_UpTo_N(ll N){
  ll i,j,ans=0;///upto N in Sqrt(N)
  for(i=1;i*i<=N;i++){
    j=N/i;
    ans+=((j*(j+1))/2)-(((i-1)*i)/2);
    ans+=((j-i)*i);
  }
  return ans;
}
ll SODUptoN(ll N){
  ll res=0,u=sqrt(N);
  for(ll i=1;i<=u;i++)
    res+=(N/i)-i;
  res*=2,res+=u;
  return res;
}
