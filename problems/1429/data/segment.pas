const maxn=1000000;
var a:array[0..maxn]of longint;
    n,x,y,t,s,i:longint;
function min(a,b:longint):longint;
begin
  if a<b then min:=a else min:=b;
end;
begin
  assign(input,'segment10.in');
  reset(input);
  assign(output,'segment10.out');
  rewrite(output);
  readln(n);
  fillchar(a,sizeof(a),0);
  for i:=1 to n do
  begin
    readln(x,y);
    if (a[x]=0)or(a[x]>y) then a[x]:=y;
  end;
  s:=0;
  t:=-1;
  for i:=0 to maxn-1 do
  begin
    if (a[i]>0) then
      if i>=t then
      begin
        inc(s);
        t:=a[i];
      end
      else
        t:=min(a[i],t);
  end;
  writeln(s);
  close(input);
  close(output);
end.
