#ifndef __j1BUFFDEBUFF_H__
#define __j1BUFFDEBUFF_H__

#include "j1Module.h"

struct Buff
{
	std::string buffdebuff_name;
	std::string type; 
	float duration;
	int oper;  //operator
	float value;
	std::string target;
};

enum Operators
{
	sum = 0,  
	substract, 
	multiply, 
	divide
};


class j1BuffDebuff : public j1Module
{
	public:
		j1BuffDebuff();

		// Destructor
		virtual ~j1BuffDebuff();

		// Called before render is available
		bool Awake(pugi::xml_node& info);

		// Called before the first frame
		bool Start();

		// Called each loop iteration
		bool Update(); 
		//bool PreUpdate();
		//bool PostUpdate();

		// Called before quitting
		bool CleanUp();
	
		pugi::xml_node LoadXMLBuffDebuff(pugi::xml_document& bd_file) const;

		//Utils
		bool AddBuffToList(Buff* bd);

		bool LoadBuffDebuff(pugi::xml_node& bd_node, Buff* bd);

		bool CheckTypeBuffDebuff(std::string type); 

		bool ApplyBuffAttributes(std::string buff_name);
		bool ApplyBuffItems(std::string buff_name);
		bool ApplyBuffTerrain(std::string buff_name);

	private: 
		
		std::list<Buff*> buffList;
		Buff* buff_debuff;

}; 











































#endif // __j1BUFFDEBUFF_H__