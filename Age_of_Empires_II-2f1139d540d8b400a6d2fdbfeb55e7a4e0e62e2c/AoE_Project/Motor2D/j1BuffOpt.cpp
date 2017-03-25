#include "j1BuffOpt.h"

j1BuffOpt::j1BuffOpt() : j1Module()
{
	name = "buffdebuff";
}

j1BuffOpt::~j1BuffOpt()
{
}

bool j1BuffOpt::Awake(pugi::xml_node & info)
{
	pugi::xml_document info_buffdebuff;
	pugi::xml_node     bd_node;
	pugi::xml_node     bd_info;

	bool ret = true;

	bd_info = LoadXMLBuffDebuff(info_buffdebuff);

	if (bd_info.empty() == false)
	{
		for (bd_node = info_buffdebuff.child("buff_debuff").child("buffs").child("name"); bd_node && ret; bd_node = bd_node.next_sibling("name"))
		{
				Buffs* bd = new Buffs();
				ret = LoadBuffDebuff(bd_node, bd);
				buffsList.push_back(bd);
		}
	}

	return ret;
}

bool j1BuffOpt::Start()
{
	return true;
}

bool j1BuffOpt::Update()
{
	return true;
}

bool j1BuffOpt::PreUpdate()
{
	return true;
}

bool j1BuffOpt::CleanUp()
{
	return true;
}

pugi::xml_node j1BuffOpt::LoadXMLBuffDebuff(pugi::xml_document & bd_file) const
{
	pugi::xml_node ret;

	char* buf;
	int size = App->fs->Load("buff_debuff.xml", &buf);
	pugi::xml_parse_result result = bd_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load xml file buff_debuff.xml. pugi error: %s", result.description());
	else
		ret = bd_file.child("buff_debuff");

	return ret;
}


bool j1BuffOpt::LoadBuffDebuff(pugi::xml_node & bd_node, Buffs * bd)
{
	bool ret = false;

	if (bd_node && bd)
	{
		pugi::xml_node node_buff;

		ret = true;

		bd->buffdebuff_name = bd_node.child_value();
		bd->type = bd_node.attribute("type").as_string();
		bd->timer_duration = bd_node.attribute("timer_duration").as_uint();
		bd->oper = bd_node.attribute("operator").as_int();
		bd->value = bd_node.attribute("value").as_float();
		bd->cast = bd_node.attribute("target").as_string();
		bd->attr_to_change = bd_node.attribute("attr_to_change").as_string();
	}
	return ret;
}

bool j1BuffOpt::ApplyBuffs(std::string buff_name, j1Player* target, std::list<Buffs*> buffList)
{

	return true;
}

Buffs SearchBuff(std::string buff_name, std::list<Buffs*> buffList)
{
	
	std::list<Buffs*>::iterator item = buffList.begin();
	while (item != buffList.end())
	{
		if ((*item)->buffdebuff_name == buff_name)
		{
			Buffs ret((*item)->timer_duration,(*item)->buffdebuff_name,(*item)->type, (*item)->attr_to_change, (*item)->value);
			return ret;
		}
		item++;
	}
}

bool j1BuffOpt::CheckAppliedBuff(std::list<Buffs*> appliedbuffList)
{
	return true;
}