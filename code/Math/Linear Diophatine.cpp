/*x'=x+(k*B/g),y'=y-(k*A/g);infinite soln
if A=B=0,C must equal 0 and any x,y is solution;
if A|B=0,(x,y)=(C/A,k)|(k,C/B)*/
bool LDE(int A,int B,int C,int*x,int*y){
  int g=gcd(A,B);
  if(C%g!=0)return false;
  int a=A/g,b=B/g,c=C/g;
  extended_gcd(a,b,x,y);//ax+by=1
  if(g<0)a*=-1;b*=-1;c*=-1;//Ensure gcd(a,b)=1
 *x*=c;*y*=c;//ax+by=c
  return true;//Solution Exists
}
