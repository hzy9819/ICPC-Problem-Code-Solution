u := 15mm;

beginfig(1)
	pickup pencircle scaled 1pt;
	z1 = (1u, 3.73u);
	z2 = (3u, 3.73u);
	z3 = (4u, 2u);
	z4 = (3u, 0.27u);
	z5 = (1u, 0.27u);
	z6 = (0u, 2u);
	draw z1--z2--z3--z4--z5--z6--z1;
	draw z1--z5--z2--z4;
    pickup pencircle scaled 3pt;
    for i=1 upto 6:
   	    draw z[i];
    endfor
	label.ulft("1", z1);
	label.urt("2", z2);
	label.rt("3", z3);
	label.lrt("4", z4);
	label.llft("5", z5);
	label.lft("6", z6);
endfig;

end.
