#ifndef GRAPH1010
#define GRAPH1010
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
#define GRAPH_ENABLED true

class plot {
public:
 FILE *gp;
 bool enabled,persist;
 plot(bool _persist=true,bool _enabled=GRAPH_ENABLED) {
 enabled=_enabled;
 persist=_persist;
  if (enabled) {
	if(persist)
		  gp=popen("set term x11 1 noraise && gnuplot -persist","w");
	else
		  gp=popen("set term x11 1 noraise && gnuplot","w");
  }
 }

 void plot_data(vector<float> x,const char* style="lines",const char* title="Data") {
 if(!enabled)
	return;
  fprintf(gp,"set title '%s' \n",title);
  fprintf(gp,"plot '-' w %s \n",style);
  for(int k=0;k<x.size();k++) {
   fprintf(gp,"%f\n",x[k]);
  }
  fprintf(gp,"e\n");
  fflush(gp);
 }

 void plot_data(vector<float> x,vector<float> y,const char* style="lines",const char* title="Data") {
 if(!enabled)
	return;
  fprintf(gp,"set title '%s' \n",title);
//  fprintf(gp,"set style line 1 lt 2 lw 2 pt 3 ps 0.5 \n");

  fprintf(gp,"plot '-' w %s \n",style);

  for(int k=0;k<x.size();k++) {
   fprintf(gp,"%f %f \n",x[k],y[k]);
  }
  fprintf(gp,"e\n");
  fflush(gp);
 }

 ~plot() {
  if(enabled)
  pclose(gp);
 }
 
};

/*
int main(int argc,char **argv) {
 plot p;
 for(int a=0;a<100;a++) {
 vector<float> x,y;
 for(int k=a;k<a+200;k++) {
   x.push_back(k);
   y.push_back(k*k);
 }
  p.plot_data(x,y);
 }
 return 0;
}
*/

#endif
