const maxn=200000;
      max=1000000;
var n,m,i,x,y,t,j,ans,keypoint,l,r:longint;
    a,opt,pre:array[1..maxn]of longint;
    rmq:array[1..maxn,0..20]of longint;
    f:array[-max..max]of longint;
    ch:char;
function find(x,y:longint):longint;
  var left,right,mid:longint;
  begin
    left:=x;right:=y;
    while left<=right do begin
      mid:=(left+right)shr 1;
      if pre[mid]<=y then left:=mid+1
      else right:=mid-1;
    end;
    find:=left;
  end;
function findmax(x,y:longint):longint;
  var i,j:longint;
  begin
    i:=0;j:=1;
    while 2*j<=y-x+1 do begin
      inc(i);
      j:=j*2;
    end;
    if rmq[x,i]>rmq[y+1-j,i] then findmax:=rmq[x,i]
    else findmax:=rmq[y+1-j,i];
  end;
begin
 for ch:='0' to '9' do begin
  assign(input,'diff'+ch+'.in');
  reset(input);
  assign(output,'diff'+ch+'.out');
  rewrite(output);
  readln(n,m);
  for i:=1 to n do read(a[i]);
  fillchar(f,sizeof(f),0);
  opt[n]:=1;
  pre[n]:=n;
  f[a[n]]:=n;
  for i:=n-1 downto 1 do begin
    opt[i]:=opt[i+1]+1;
    pre[i]:=pre[i+1];
    if (f[a[i]]>0)and(f[a[i]]-i<opt[i]) then begin
       opt[i]:=f[a[i]]-i;
       pre[i]:=f[a[i]]-1;
    end;
    f[a[i]]:=i;
  end;
  fillchar(rmq,sizeof(rmq),0);
  for i:=1 to  n do rmq[i,0]:=opt[i];
  i:=1;t:=2;
  while t<=n do begin
    for j:=1 to n-t+1 do begin
      if rmq[j,i-1]>rmq[j+(1 shl (i-1)),i-1] then rmq[j,i]:=rmq[j,i-1]
      else rmq[j,i]:=rmq[j+(1 shl (i-1)),i-1]
    end;
    inc(i);
    t:=t*2;
  end;
  for i:=1 to m do begin
    readln(l,r);
    inc(l);inc(r);
    if l>r then begin
       j:=l;l:=r;r:=j;
    end;
    keypoint:=find(l,r);
    ans:=0;
    if keypoint>l then ans:=findmax(l,keypoint-1);
    if (keypoint<=r)and(r-keypoint+1>ans) then begin
       ans:=r-keypoint+1;
    end;
    writeln(ans);
  end;
  close(input);
  close(output);
 end;
end.
