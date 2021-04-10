u := 20mm;

beginfig(1)
	pickup pencircle scaled 1pt;
	z1 = (0u, 0u);
	z4 = (1u, 1u);
	z3 = (0u, 1u);
	z2 = (1u, 0u);
	ahlength := 0.2u;
	ahangle := 25;
	drawarrow z1{dir 30}..z4;
	drawarrow z4{dir 210}..z1;
	drawarrow z4--z2;
	drawarrow z2--z1;
	drawarrow z3--z4;
	drawarrow z1--z3;
	label.lft("1", z1);
	label.rt("2", z2);
	label.lft("3", z3);
	label.rt("4", z4);
endfig;

end.
