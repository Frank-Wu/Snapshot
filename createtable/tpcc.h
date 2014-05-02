#include <string>

const int warehouse_fields_num=9;
const std::string warehouse_fields_name[warehouse_fields_num]={
	"w_id",
	"w_name",
	"w_street_1",
	"w_street_2",
	"w_city",
	"w_state",
	"w_zip",
	"w_tax",
	"w_ytd"
};
const int warehouse_fields_size[warehouse_fields_num]={
	sizeof(int),
	16,
	32,
	32,
	32,
	2,
	9,
	sizeof(float),
	sizeof(float)
};

const int district_fields_num=11;
const std::string district_fields_name[district_fields_num]={
	"d_id",
	"d_w_id",
	"d_name",
	"d_street_1",
	"d_street_2",
	"d_city",
	"d_state",
	"d_zip",
	"d_tax",
	"d_ytd",
	"d_next_o_id"
};
const int district_fields_size[district_fields_num]={
	sizeof(int),
	sizeof(int),
	16,
	32,
	32,
	32,
	2,
	9,
	sizeof(float),
	sizeof(float),
	sizeof(int)
};

const int item_fields_num=5;
const std::string item_fields_name[item_fields_num]={};
const int item_fields_size[item_fields_num]={};

const int customer_fields_num=21;
const std::string customer_fields_name[customer_fields_num]={};
const int customer_fields_size[customer_fields_num]={};

const int history_fields_num=8;
const std::string history_fields_name[history_fields_num]={};
const int history_fields_size[history_fields_num]={};

const int stock_fields_num=17;
const std::string stock_fields_name[stock_fields_num]={};
const int stock_fields_size[stock_fields_num]={};

const int order_fields_num=8;
const std::string order_fields_name[order_fields_num]={};
const int order_fields_size[order_fields_num]={};

const int new_order_fields_num=3;
const std::string new_order_fields_name[new_order_fields_num]={};
const int new_order_fields_size[new_order_fields_num]={};

const int order_line_fields_num=10;
const std::string order_line_fields_name[order_line_fields_num]={};
const int order_line_fields_size[order_line_fields_num]={};
