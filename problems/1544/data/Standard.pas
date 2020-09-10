program rmq;
  var n,m,k:longint;
      a:array[1..200000,0..17]of longint;
      log:array[1..200000]of byte;
      len:array[0..20]of longint;
procedure pre_rmq;
  var i:longint;
begin
 log[1]:=0;
 for i:=2 to n do
   log[i]:=log[i shr 1]+1;
 k:=log[n];
 len[0]:=1;
 for i:=1 to 20 do
   len[i]:=len[i-1]*2;
end;
procedure init;
  var i:longint;
 begin
  readln(n);
  for i:=1 to n do
   read(a[i,0]);
  pre_rmq;
 end;
function max(x,y:longint):longint;
 begin
  if x>y then max:=x
         else max:=y;
 end;
procedure work;
var i,j,x,y:longint;
begin
  for j:=1 to k do
    for i:=1 to n-len[j]+1 do
      a[i,j]:=max(a[i,j-1],a[i+len[j-1],j-1]);
  readln(m);
  for i:=1 to m do
  begin
    readln(x,y);
    j:=log[y-x+1];
    writeln(max(a[x,j],a[y-len[j]+1,j]));
  end;
end;
begin

  init;
  work;

end.
