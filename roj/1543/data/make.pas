var ch:char;
    i,n,m,l,r,t:longint;
begin
  randomize;
  for ch:='0' to '1' do begin
    assign(output,'diff'+ch+'.in');
    rewrite(output);
    n:=100;
    m:=n;
    writeln(n,' ',m);
    for i:=1 to n do write(random(2000000)-1000000,' ');writeln;
    for i:=1 to m do begin
      l:=random(n);
      r:=random(n);
      if l>r then begin
         t:=l;l:=r;r:=t;
      end;
      writeln(l,' ',r);
    end;
    close(output);
  end;
end.
