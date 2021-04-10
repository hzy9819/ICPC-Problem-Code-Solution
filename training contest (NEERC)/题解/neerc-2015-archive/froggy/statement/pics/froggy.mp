u := 0.7cm;
w := 10;
h := 6;

pair p[];
p[1] := (2, 2);
p[2] := (2, 4);
p[3] := (5, 1);
p[4] := (5, 3);
p[5] := (8, 2);
p[6] := (7, 5);
p[7] := (9, 4);

def stone(expr p, i) =
    dotlabel.bot(i, p scaled u);
enddef;

def river =
    pickup pencircle scaled 0.5pt;
    draw ((0, 0){dir(30)} .. {dir(30)}(w, 0)) scaled u;
    draw ((0, 0){dir(30)} .. {dir(30)}(w, 0)) shifted (0, h) scaled u;

    pickup pencircle scaled 1pt;

    for i = 1 step 1 until 7:
      stone(p[i], decimal(i));
    endfor;

    draw ((0, 0) -- (0, h)) scaled u;
    draw ((10, 0) -- (w, h)) scaled u;
enddef;

beginfig(1)
    river;
    draw ((0, 2) -- p[1] -- p[4] -- p[5] -- p[7] -- (w, 4)) scaled u;
endfig;

beginfig(2)
    river;
    stone((4.5, 4.5), "+");
    draw ((0, 4) -- p[2] -- p[6] -- p[7] -- (w, 4)) scaled u;
endfig;

end.
