{$r+,s+,q+}
var
   son,fa,top,w,mark,ss,dep : array[0..100000] of longint;
   first,next,endl,sum	    : array[0..100000] of longint;
   i,j,k,l,m,n,s,tot,t	    : longint;
   s1			    : string[3];
   s2			    : string[5];
   ch			    : char;

function max(a,b :longint ):longint;
begin
   if a>b then exit(a);
   exit(b);
end; { max }

procedure setl(x,y: longint );
begin
   inc(tot);
   next[tot]:=first[x];
   first[x]:=tot;
   endl[tot]:=y;
end; { setl }

procedure dfs1(x,f :longint );
var k,l,m: longint;
begin 
   ss[x]:=1;  fa[x]:=f;
   k:=first[x];  l:=endl[k];
   m:=0;
   dep[x]:=dep[f]+1;
   while k<>0 do
   begin
      if l<>f then
	 begin
	    dfs1(l,x);
	    inc(ss[x],ss[l]);
	    if ss[l]>ss[m] then m:=l;
	 end;
      k:=next[k];  l:=endl[k]; 
   end;
   son[x]:=m;
end; { dfs1 }

procedure dfs2(x,f :longint );
var k,l	: longint;
begin
   k:=first[x];  l:=endl[k];
   if son[x]<>0 then
   begin
      inc(tot);
      top[son[x]]:=top[x];
      mark[son[x]]:=tot;
      dfs2(son[x],x);
   end;
   while k<>0 do
   begin
      if (l<>f)and(l<>son[x])then
      begin
	 inc(tot);
	 top[l]:=l;
	 mark[l]:=tot;
	 dfs2(l,x);
      end;
      k:=next[k];  l:=endl[k];
   end;
end; { dfs2 }

procedure tree1(k,m,n,q,c: longint );
var mid,z1,z2 : longint;
begin
   if(m>q)or(n<q) then exit;
   if m=n then
   begin
      w[k]:=c; sum[k]:=c;
      exit;
   end;
   z1:=k<<1;   z2:=z1+1;
   mid:=(m+n)>>1;
   tree1(z1,m,mid,q,c);
   tree1(z2,mid+1,n,q,c);
   w[k]:=max(w[z1],w[z2]);
   sum[k]:=sum[z1]+sum[z2];
end; { tree1 }

function tree2(k,m,n,p,q :longint ):longint;
var mid,z1,z2 : longint;
begin
   if (m>q)or(n<p) then exit(-maxlongint);
   if (m>=p)and(n<=q) then exit(w[k]);
   z1:=k<<1;  z2:=z1+1;
   mid:=(m+n)>>1;
   exit(max(tree2(z1,m,mid,p,q),tree2(z2,mid+1,n,p,q)));
end; { tree2 }

function tree3(k,m,n,p,q :longint ):longint;
var mid,z1,z2 : longint;
begin
   if (m>q)or(n<p) then exit(0);
   if (m>=p)and(n<=q) then exit(sum[k]);
   z1:=k<<1;  z2:=z1+1;
   mid:=(m+n)>>1;
   exit(tree3(z1,m,mid,p,q)+tree3(z2,mid+1,n,p,q));
end; { tree3 }

procedure swap(var a,b :longint );
var l : longint;
begin
   l:=a;  a:=b;  b:=l;
end; { swap }

function find(x,y: longint ):longint;
var f1,f2 : longint;
begin
   f1:=top[x];  f2:=top[y];
   if f1<>f2 then
   begin
      if dep[f1]<dep[f2] then swap(x,y);
      if dep[f1]<dep[f2] then swap(f1,f2);
      exit(max(find(fa[f1],y),tree2(1,1,tot,mark[f1],mark[x])));
   end;
   if dep[x]>dep[y] then swap(x,y);
   exit(tree2(1,1,tot,mark[x],mark[y]));
end; { find }

function qsum(x,y: longint ):longint;
var f1,f2 : longint;
begin
   f1:=top[x];  f2:=top[y];
   if f1<>f2 then
   begin
      if dep[f1]<dep[f2] then swap(x,y);
      if dep[f1]<dep[f2] then swap(f1,f2);
      exit(qsum(fa[f1],y)+tree3(1,1,tot,mark[f1],mark[x]));
   end;
   if dep[x]>dep[y] then swap(x,y);
   exit(tree3(1,1,tot,mark[x],mark[y]));
end; { qsum }

begin
   t:=1;
   for t:=t downto 1 do
   begin
      readln(n);
      fillchar(first,sizeof(first),0);
      fillchar(son,sizeof(son),0);
      fillchar(dep,sizeof(dep),0);
      fillchar(w,sizeof(w),$80);
      fillchar(sum,sizeof(sum),0);
      tot:=0;
      for i:=1 to n-1 do
      begin
	 readln(k,l);
	 setl(k,l);
	 setl(l,k);
      end;
      ss[0]:=0;  dep[0]:=0; 
      dfs1(1,0); 
      top[1]:=1;  tot:=1;  mark[1]:=1;
      dfs2(1,0);
      for i:=1 to n do
      begin
	 read(k);
	 tree1(1,1,tot,mark[i],k);
      end;
      readln(m);
      for i:=1 to m do
      begin
	 read(ch);
	 if ch='Q' then
	 begin
	    readln(s1,k,l);
	    if s1[1]='M' then
	    writeln(find(k,l))
	    else writeln(qsum(k,l));
	 end;
	 if ch='C' then
	 begin
	    readln(s2,k,l);
	    tree1(1,1,tot,mark[k],l);
	 end;
      end;
   end;
end.