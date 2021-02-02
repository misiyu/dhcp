// create by weiguohua
#include "if_info.h"

If_info::If_info(){
	this->if_n = 0;
	this->get_if_info();
}

int If_info::get_if_info(){
	FILE *fp = popen("ip link","r");
	char buff[500];
	while(fgets(buff,500,fp) != NULL){
		string line = buff ;
		int tmp1 = line.find(':',0);
		int tmp2 = line.find(':',tmp1+1) ;
		string if_name = line.substr(tmp1+2,tmp2-tmp1-2);
		IF_STATE state = init;
		if(line.find("UP",0) == string::npos) state = off;
		fgets(buff,500,fp);
		line = buff ;
		tmp1 = line.find(':',0);
		unsigned char mac[6];
		unsigned int tmp;
		int read_i = tmp1-2 ;
		bool is_lo = true ;
		for (int i = 0; i < 6; ++i) {
			sscanf(buff+read_i,"%x",&tmp);
			if(tmp != 0) is_lo = false ;
			mac[i] = tmp ;
			read_i += 3 ;
		}
		if(!is_lo){
			this->add_if(if_name.data() , mac , state);
		}
	}
	for (int i = 0; i < this->if_n; ++i) {
		cout << this->ndn_ifs[i].if_name << endl ;
		for (int j = 0; j < 6; ++j) printf("%02x:",this->ndn_ifs[i].mac[j] ) ;
		cout << endl ;
		cout << this->ndn_ifs[i].state << endl ;
	}
	pclose(fp) ;
	return 0 ;
}

int If_info::add_if(const char *if_name , unsigned char *mac , IF_STATE state){
	for (int i = 0; i < this->if_n; ++i) {
		if(strcmp(this->ndn_ifs[i].if_name , if_name) == 0){
			if(!(this->ndn_ifs[i].state == active && state==init))
				this->ndn_ifs[i].state = state ;
			return 0 ;
		}
	}
	memcpy(this->ndn_ifs[this->if_n].if_name , if_name, sizeof(if_name));
	memcpy(this->ndn_ifs[this->if_n].mac , mac , 6);
	this->ndn_ifs[this->if_n].state = state ;
	this->if_n ++ ;
	
	return 0;
}
