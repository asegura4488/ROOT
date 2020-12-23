
#include <stdio.h>
#include <math.h>

typedef double real;

#define N 4	/* Number of first-order equations */
#define GM 1	/* Constant in Coulomb's law */


/* Determine (vector) dx/dt, given (vector) x and t */

void deriv(int n, real x[], real t, real dxdt[])
{
    real r2, r3i;

    dxdt[0] = x[2];
    dxdt[1] = x[3];

    r2 = x[0]*x[0] + x[1]*x[1];		/* Inverse-square force law */
    r3i = GM / (r2*sqrt(r2));

    dxdt[2] = -x[0]*r3i;
    dxdt[3] = -x[1]*r3i;
}


/* Euler method */

void euler_step(int n, real x[], real* t, real dt)
{
    real dxdt[N];
    int i;

    deriv(n, x, *t, dxdt);

    *t += dt;
    for (i = 0; i < n; i++) x[i] += dt*dxdt[i];
}


/* Midpoint method */

void midpoint_step(int n, real x[], real* t, real dt)
{
    real dxdt[N], xtmp[N];
    int i;

    deriv(n, x, *t, dxdt);
    for (i = 0; i < n; i++) xtmp[i] = x[i] + 0.5*dt*dxdt[i];
    deriv(n, xtmp, *t + 0.5*dt, dxdt);

    *t += dt;
    for (i = 0; i < n; i++) x[i] += dt*dxdt[i];
}


/* Runge-Kutta-4 method */

void rk4_step(int n, real x[], real* t, real dt)
{
    real dxdt[N], xtmp[N], dx1[N], dx2[N], dx3[N], dx4[N];
    int i;

    deriv(n, x, *t, dxdt);
    for (i = 0; i < n; i++) {
	dx1[i] = dt*dxdt[i];
	xtmp[i] = x[i] + 0.5*dx1[i];
    }

    deriv(n, xtmp, *t + 0.5*dt, dxdt);
    for (i = 0; i < n; i++) {
	dx2[i] = dt*dxdt[i];
	xtmp[i] = x[i] + 0.5*dx2[i];
    }

    deriv(n, xtmp, *t + 0.5*dt, dxdt);
    for (i = 0; i < n; i++) {
	dx3[i] = dt*dxdt[i];
	xtmp[i] = x[i] + dx3[i];
    }

    deriv(n, xtmp, *t + dt, dxdt);
    for (i = 0; i < n; i++) {
	dx4[i] = dt*dxdt[i];
    }

    *t += dt;
    for (i = 0; i < n; i++)
	x[i] += (dx1[i] + dx4[i])/6 + (dx2[i] + dx3[i])/3;
}

static real e0;

/* Energy (inverse-square case ONLY!) */

real energy(int n, real x[])
{
    return 0.5 * (x[2]*x[2] + x[3]*x[3])
			- GM / sqrt(x[0]*x[0] + x[1]*x[1]);
}


void output(int n, real x[], real t)
{
    int i;

    printf("%f", t);
    for (i = 0; i < n; i++)  printf(" %f", x[i]);
    printf(" %f", energy(n, x) - e0);
    printf("\n");
}


main(int argc, char** argv)
{
    /* General integrator x(t). */

    /* Default integration parameters and initial conditions: */

    real t = 0, x[N] = {1.0, 0.0, 0.0, 0.75};
    real t_max = 100, dt = 0.01;
    void (*integrate)() = midpoint_step;	/* Pointer to the integrator */

    int i;

    /* Parse the argument list. */

    for (i = 0; i < argc; i++)
	if (argv[i][0] == '-') {
	    switch (argv[i][1]) {

		case 'd':	dt = atof(argv[++i]); break;
		case 'e':	integrate = euler_step; break;
		case 'm':	integrate = midpoint_step; break;
		case 'r':	integrate = rk4_step; break;
		case 't':	t_max = atof(argv[++i]); break;
		case 'v':	x[3] = atof(argv[++i]); break;
	    }
	}

    e0 = energy(N, x);

    while (t < t_max) {
	output(N, x, t);
	integrate(N, x, &t, dt);
    }
    output(N, x, t);
}
