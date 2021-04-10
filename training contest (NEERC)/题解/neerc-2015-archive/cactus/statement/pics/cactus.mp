u := 10mm;

beginfig(1)

z1 = (1u,2u);
z2 = (2u,2u);
z3 = (3u,2u);
z4 = (4u,2u);
z5 = (1u,1u);
z6 = (3u,1u);

pickup pencircle scaled 1pt;

draw z1--z2--z5--z6--z2--z3--z4;

pickup pencircle scaled 3pt;

for i=1 upto 6:
	draw z[i];
endfor

label.top("1", z1);
label.top("2", z2);
label.top("3", z3);
label.top("4", z4);
label.llft("5", z5);
label.lrt("6", z6);

endfig;

beginfig(2)

z1 = (1u,1u);
z2 = (2u,2u);
z3 = (2u,3u);
z4 = (3u,4u);
z5 = (3u,5u);
z6 = (2u,6u);
z7 = (1u,5u);
z8 = (1u,4u);
z9 = (3u,3u);
z10 = (4u,4u);
z11 = (5u,4u);
z12 = (5u,5u);
z13 = (4u,5u);
z14 = (3u,2u);
z15 = (4u,3u);

pickup pencircle scaled 1pt;

draw z1--z2--z3--z4--z5--z6--z7--z8--z3;
draw z2--z9--z10--z11--z12--z13--z10;
draw z2--z14--z9--z15--z10;

pickup pencircle scaled 3pt;

for i=1 upto 15:
	draw z[i];
endfor

label.bot("1", z1);
label.bot("2", z2);
label.llft("3", z3);
label.rt("4", z4);
label.rt("5", z5);
label.top("6", z6);
label.lft("7", z7);
label.lft("8", z8);
label.lrt("9", z9);
label.lrt("10", z10);
label.lrt("11", z11);
label.urt("12", z12);
label.ulft("13", z13);
label.bot("14", z14);
label.lrt("15", z15);

endfig;

end.
