u := 0.5cm;

numeric h[];
h[1] := 3;
h[2] := 4;
h[3] := 2;
h[4] := 1;
h[5] := 3;
h[6] := 3;
h[7] := 2;
h[8] := 4;

path sq;
sq = (0, 0) -- (0, 1) -- (1, 1) -- (1, 0) -- cycle;

def landscape =
    pickup pencircle scaled 0.5pt;

    for x = 1 step 1 until 8:
        for y = 1 step 1 until h[x]:
            fill sq shifted (x - 1, y - 1) scaled u withcolor 0.9 white;
            square(x, y);
        endfor;
    endfor;
enddef;

def square(expr x, y) =
    draw sq shifted (x - 1, y - 1) scaled u;
enddef;

beginfig(1)
    landscape;
endfig;

beginfig(2)
    landscape;
    square(6, 4);
    square(7, 3);
    square(7, 4);
    square(7, 5);
endfig;

end.
