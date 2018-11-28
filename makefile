#makefile
UROOT=-pthread -stdlib=libc++ -std=c++11 -m64 -I/Users/samueletorelli/Documents/root/build/include -L/Users/samueletorelli/Documents/root/build/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -lpthread -stdlib=libc++ -lm -ldl
#
simulation: ScatteringDet.o EnergyLossDet.o Generator.o Detector.o
	g++ -o simulation simulation.cpp ScatteringDet.o EnergyLossDet.o Generator.o $(UROOT)
#
Detector.o: Detector.cc
	g++ -c Detector.cc $(UROOT)
#
Generator.o: Generator.cc
	g++ -c Generator.cc $(UROOT)
#
ScatteringDet.o: ScatteringDet.cc Detector.o
	g++ -c ScatteringDet.cc Detector.o $(UROOT)
#
EnergyLossDet.o: EnergyLossDet.cc Detector.o
	g++ -c EnergyLossDet.cc Detector.o $(UROOT)
#

clean:
	rm *.o


