program CQF_GCD;
type num=array[0..3000] of integer;
var a,b:num;
procedure init;
var i:longint;
    s:ansistring;
begin
   readln(s);
   a[0]:=length(s);
   for i:=1 to a[0] do
      a[i]:=ord(s[a[0]+1-i])-48;
   readln(s);
   b[0]:=length(s);
   for i:=1 to b[0] do
      b[i]:=ord(s[b[0]+1-i])-48;
end;
procedure work;
var ti,i,j:longint;
procedure div2(var a:num);
var i,k:longint;
begin
   k:=0;
   for i:=a[0] downto 1 do begin
      k:=k*10+a[i];
      a[i]:=k shr 1;
      k:=k and 1;
   end;
   while a[a[0]]=0 do
      dec(a[0]);
end;
procedure minus(var a,b:num);
var i:longint;
begin
   for i:=1 to a[0] do begin
      dec(a[i],b[i]);
      if a[i]<0 then begin
         dec(a[i+1]);
         inc(a[i],10);
      end;
   end;
   while a[a[0]]=0 do
      dec(a[0]);
end;
function compare(var a,b:num):longint;
var i:longint;
begin
   if a[0]<>b[0] then
      exit(ord(a[0]>b[0])*2-1);
   for i:=a[0] downto 1 do
      if a[i]<>b[i] then
         exit(ord(a[i]>b[i])*2-1);
   compare:=0;
end;
begin
   ti:=0;
   while compare(a,b)<>0 do
      if odd(a[1])and odd(b[1]) then
         if compare(a,b)=1 then
            minus(a,b)
         else
            minus(b,a)
      else begin
         if not odd(a[1])and not odd(b[1]) then
            inc(ti);
         if not odd(a[1]) then
            div2(a);
         if not odd(b[1]) then
            div2(b);
      end;
   for i:=1 to ti do begin
      for j:=1 to a[0] do
         a[j]:=a[j]+a[j];
      for j:=1 to a[0] do
         if a[j]>9 then begin
            dec(a[j],10);
            inc(a[j+1]);
         end;
      if a[a[0]+1]>0 then
         inc(a[0]);
   end;
   for i:=a[0] downto 1 do
      write(a[i]);
   writeln;
end;
begin
   assign(input,'gcd6.in');
   assign(output,'gcd6.out');
   reset(input);
   rewrite(output);
   init;
   work;
   close(input);
   close(output);
end.
