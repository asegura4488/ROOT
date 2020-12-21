void Matrix(){
TMatrixD m(2,2);
m[0][0] = -2.;
m[0][1] = -4.;
m[1][0] = -2.;
m[1][1] = -9.;

TMatrixD n(2,2);
n = m;
Double_t det;
n.Invert(&det);

m.Print();
n.Print();

TMatrixD t(2,2);
t = n*m;
t.Print();

}
