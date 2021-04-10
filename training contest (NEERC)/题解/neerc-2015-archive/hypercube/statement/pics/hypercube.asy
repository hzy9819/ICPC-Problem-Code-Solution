// NOTE: This code is not using module "three" to produce a higher-quality vector rendering instead of OpenGL-rendered image
// Perspecive projection of 3D space into 2D is manually defined

//==================================================== definitions ====================================================

// general sizes
void begin() {
  currentpicture=new picture; 
  unitsize(2cm);
  size(0, 9cm);
}

pen linepen = gray(0.3);
transform lblScale = scale(0.6);

// perspective projection from 3D to 2D
struct perspective {
  triple cam;
  triple p0;
  triple u;
  triple v;

  void operator init(triple cam, triple p0) {
    this.cam = cam;
    this.p0 = p0;
    triple r = p0 - cam;
    this.u = unit((r.y, -r.x, 0));
    this.v = unit(cross(this.u, r));
  }

  pair project(triple p) {
    triple r = p - cam;
    return (dot(r, this.u), dot(r, this.v));
  }
}

// a particular perspective we'll be using
perspective currentperspective = perspective((7.4, -15, 4.1), (1.5, 1.5, 1.5));

pair p3(triple p) {
  return currentperspective.project(p);
}

// 4D transformation and points

// ortographic projection of 4th dimension
triple proj4 = (0.35, 0.35, 0.45); 

int DX = 0;
int DY = 1;
int DZ = 2;
int DT = 3;

struct transform4 {
   real[] c;
   real[][] m;
   
   void operator init(int dx, int dy, transform t) {
     this.c = new real[4];
     this.m = new real[4][4];
     for (int i = 0; i < 4; ++i) {
       this.c[i] = 0;
       for (int j = 0; j < 4; ++j)
         this.m[i][j] = 0;
       this.m[i][i] = 1;
     }
     this.c[dx] = t.x;
     this.c[dy] = t.y;
     this.m[dx][dx] = t.xx;
     this.m[dx][dy] = t.xy;
     this.m[dy][dx] = t.yx;
     this.m[dy][dy] = t.yy;
   }
}
                  
struct p4 {
  string lbl;
  real x;
  real y;
  real z;
  real t;
  align align0;
  align align;

  void operator init(string lbl, real x, real y, real z, real t, align align0 = NW, align align = align0) {
    this.lbl = lbl;
    this.x = x;
    this.y = y;
    this.z = z;
    this.t = t;
    this.align0 = align0;
    this.align = align;
  }

  void apply(transform4 t) {
    unravel t;
    real[] a = {this.x, this.y, this.z, this.t};
    real[] b = c[:];
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        b[i] += m[i][j] * a[j];
    this.x = b[DX];
    this.y = b[DY];
    this.z = b[DZ];
    this.t = b[DT];
  }

  // Orthographic projection 4D -> 3D, the -> 2D
  pair project() {
    return p3((this.x + proj4.x * this.t, this.y + proj4.y * this.t, this.z + proj4.z * this.t));
  }
}


p4[] pts = {
  p4("A", 1, 1, 2, 0),
  p4("B", 1, 2, 2, 0),
  p4("C", 2, 2, 2, 0),
  p4("D", 2, 1, 2, 0),
  p4("E", 1, 1, 1, 0),
  p4("F", 1, 2, 1, 0),
  p4("G", 2, 2, 1, 0),
  p4("H", 2, 1, 1, 0),
  p4("I", 1, 1, 0, 0),
  p4("J", 1, 2, 0, 0),
  p4("K", 2, 2, 0, 0),
  p4("L", 2, 1, 0, 0),
  p4("M", 1, 1, -1, 0),
  p4("N", 1, 2, -1, 0),
  p4("O", 2, 2, -1, 0),
  p4("P", 2, 1, -1, 0),
  p4("Q", 1, 1, -2, 0, NW, SW),
  p4("R", 1, 2, -2, 0, NW, SW),
  p4("S", 2, 2, -2, 0, NW, SW),
  p4("T", 2, 1, -2, 0, NW, SW),

  p4("E1", 0, 1, 1, 0, SE),
  p4("F1", 0, 2, 1, 0, SE),
  p4("I1", 0, 1, 0, 0, SE),
  p4("J1", 0, 2, 0, 0, SE),

  p4("G1", 3, 2, 1, 0, SE),
  p4("H1", 3, 1, 1, 0, SE),
  p4("K1", 3, 2, 0, 0, SE),
  p4("L1", 3, 1, 0, 0, SE),

  p4("E2", 1, 0, 1, 0, NE),
  p4("H2", 2, 0, 1, 0, NE),
  p4("I2", 1, 0, 0, 0, NE),
  p4("L2", 2, 0, 0, 0, NE),

  p4("F2", 1, 3, 1, 0, NE),
  p4("G2", 2, 3, 1, 0, NE),
  p4("J2", 1, 3, 0, 0, NE),
  p4("K2", 2, 3, 0, 0, NE),
};

pair operator cast(p4 p) {
  return p.project();
}

path operator --(p4 a, p4 b) {
  return a.project()--b.project();
}

p4 p(string s) {
  for (int i = 0; i < pts.length; ++i) {
    if (pts[i].lbl == s)
      return pts[i];
  }
  write("Point not found '" + s + "'");
  return null;
}

p4 operator cast(string s) {
  return p(s);
}

void line(p4 a, p4 b) {
  draw(a--b, linepen, DotMargins);
}

void square(p4 a, p4 b, p4 c, p4 d) {
  line(a, b);
  line(b, c);
  line(c, d);
  line(d, a);
}

int cnt(string s) {
  int cnt;
  for (int i = 0; i < length(s); ++i) {
    string c = substr(s, i, 1);
    if (c >= "A" && c <= "Z") 
      ++cnt;
  }
  return cnt;
}

string extract(string s, int idx) {
  int prev;
  int cnt;
  for (int i = 0; i < length(s); ++i) {
    string c = substr(s, i, 1);
    if (c >= "A" && c <= "Z") {
      if (cnt > idx) 
        return substr(s, prev, i - prev);
      prev = i;
      ++cnt;
    }
  }
  return substr(s, prev);
}

void line(string s) {
  for (int i = 1; i < cnt(s); ++i)
    line(extract(s, i - 1), extract(s, i));
}

void square(string s) {
  square(extract(s, 0), extract(s, 1), extract(s, 2), extract(s, 3));
}

void trans4(string s, transform4 t) {
  for (int i = 0; i < cnt(s); ++i) {
    p(extract(s, i)).apply(t);
  }
}

void fold(string s, int dx, real x0, int dy, real y0) {
  trans4(s, transform4(dx, dy, rotate(90, (x0, y0))));
}

void dots() {
  for (int i = 0; i < pts.length; ++i) {
    p4 p = pts[i];
    if (p.t == 0) 
      dot(p);
    else 
      dot(p, NoFill);
    string s = p.lbl;
    if (length(s) > 1)
      s = substr(s, 0, 1) + "_" + substr(s, 1);
    align a = p.t == 0 ? p.align0 : p.align;
    label(lblScale * ("$" + s + "$"), p, a);
  }
}

void axes() {
  pair O = p3((0,0,-2));
  pair X = p3((1,0,-2));
  pair Y = p3((0,1,-2));
  pair Z = p3((0,0,-1));
  draw(O--X, Arrow);
  draw(O--Y, Arrow);
  draw(O--Z, Arrow);
  label("$x$", X, NE);
  label("$y$", Y, SE);
  label("$z$", Z, NW);
}

void axis4() {
  pair O = p3((0,0,-2));
  pair T = p4("", 0, 0, -2, 1).project();
  draw(O--T, Arrow);
  label("$t$", T, NW);
}

void net() {
  square("ABCD");
  square("MNOP");
  square("QRST");

  line("AEIMQ");
  line("BFJNR");
  line("CGKOS");
  line("DHLPT");

  square("E1F1J1I1");
  square("H1G1K1L1");
  square("E2H2L2I2");
  square("F2G2K2J2");

  line("E1EHH1");
  line("F1FGG1");
  line("E2EFF2");
  line("H2HGG2");

  line("I1ILL1");
  line("J1JKK1");
  line("I2IJJ2");
  line("L2LKK2");
}

void produce(string name) {
  net();
  dots();
  axes();
  shipout(name);
}

//==================================================== hypercube1 ====================================================

begin();
produce("hypercube1");

//==================================================== hypercube2 ====================================================

begin();

fold("G1H1K1L1", DX, 2, DT, 0);
fold("F2G2K2J2", DY, 2, DT, 0);
axis4();
produce("hypercube2");

//==================================================== hypercube3 ====================================================

begin();

fold("E1F1I1J1", DT, 0, DX, 1);
fold("E2H2I2L2", DT, 0, DY, 1);
axis4();
produce("hypercube3");

//==================================================== hypercube4 ====================================================

begin();

fold("QRST", DT, 0, DZ, -1);
fold("MNOPQRST", DT, 0, DZ, 0);
fold("ABCD", DZ, 1, DT, 0);
axis4();
produce("hypercube4");
