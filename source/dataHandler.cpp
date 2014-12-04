#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <3ds.h>
#include "dataHandler.h"
#include "main.h"
#include "application.h"
#include "download.h"
#include "gui.h"
#include "file.h"
#include "picojson.h"

using namespace std;

vector<Application_s> topApps;
vector<Application_s> topGames;
vector<Application_s> overviewApps;
vector<Application_s> staffSelectApps;

Result updateAppList(vector<Application_s> *AppList, char* jsonURL){
	print("updateAppList() is not yet implamentet\n");
	vector<Application_s> tempV;
	const char* jsonsource = downloadFile(jsonURL);
	/* Parse json and put it into the temp vector */
	picojson::value v;
    char * json = (char*) malloc(strlen(jsonsource)+1);
    strcpy(json, jsonsource);
    string err = picojson::parse(v, json, json + strlen(json));
	print(err.c_str());
    picojson::array list = v.get("Apps").get<picojson::array>();
	
	Application_s app;
    for (picojson::array::iterator iter = list.begin(); iter != list.end(); iter++) {
		app.GUID =          (char*)(*iter).get("guid").get<string>().c_str();
		app.name =          (char*)(*iter).get("name").get<string>().c_str();
		app.publisher =     (char*)(*iter).get("publisher").get<string>().c_str();
		app.version =       (char*)(*iter).get("version").get<string>().c_str();
		app.description =   (char*)(*iter).get("description").get<string>().c_str();
		app.category =      (char*)(*iter).get("category").get<string>().c_str();
		app.subcategory =   (char*)(*iter).get("subcategory").get<string>().c_str();
		app.othercategory = (char*)(*iter).get("othercategory").get<string>().c_str();
		app._3dsx         = (char*)(*iter).get("3dsx").get<string>().c_str();
		app.smdh =          (char*)(*iter).get("smdh").get<string>().c_str();
		//app.raiting =       (*iter).get("rating").get<int>();
		tempV.push_back(app);
    }
	
	*AppList = tempV;
	if(!AppList->empty()) // NULL/Empty check
		return 0;
	else{
		print("Error, failed to do updateAppList()\n");
		return -1;
	}
}