#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const string DOCTYPE="<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
const string SVG="<svg width=\"106.03mm\" height=\"23.28mm\" viewBox=\"0 0 106.03 23.28\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">";
const string G_BEGIN="<g transform=\"translate(0,0)\"><g transform=\"scale(100,-100)\">";
const string PATH_BEGIN="<path fill=\"none\" stroke=\"red\" stroke-width=\"0.1\" d=\"";

int main(int argc,char*argv[])
{
	//exclude command error
	if(argc<2)
	{
		cerr<<"error: no file name"<<endl;
		return 1;
	}
	else if(argc>2)
	{
		cerr<<"error: too many arguments"<<endl;
		return 1;
	}

	//get foil name from file name
	string foilname=argv[1];
	for(int i=0;i<4;i++)foilname.pop_back();
	
	//make new svg file
	ofstream newSVGfile;
	newSVGfile.open(foilname+".svg",ios::trunc);

	//write header(?)
	newSVGfile<<DOCTYPE<<endl<<SVG<<endl;

	//write title
	newSVGfile<<"<title>Airfoil plot "<<foilname<<"</title>"<<endl;

	//write g_begin
	newSVGfile<<G_BEGIN;
	
	//open dat file
	ifstream originalDATfile;
	originalDATfile.open(argv[1]);
	if(!originalDATfile)
	{
		cerr<<"error: could not open \""<<argv[1]<<"\""<<endl;
		return 1;
	}
	string buffer;

	//discard first line of dat file
	getline(originalDATfile,buffer);

	//write path
	newSVGfile<<PATH_BEGIN;
	int flag=0;
	while(getline(originalDATfile,buffer))
	{
		newSVGfile<<(flag?" L ":" M ")<<buffer;
		flag++;
	}
	newSVGfile<<"\"></path></g></g></svg>"<<endl;

	//close new file
	newSVGfile.close();

	//finish
	cout<<"success"<<endl;
	return 0;
}


