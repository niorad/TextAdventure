
//each of the different possible values
typedef enum json_values {ARRAY, OBJECT, PRIMITIVE } JSON_values;

//represents each type of primitive
typedef enum primitive_type {BOOL, STRING, INT} Primitive_Type;

//represents an array
typedef struct json_array {
	void *value;                        //pointer to the first element in the array. Array could be json_array, json_object, or json_primitive
} JSON_array;

//represents an object
typedef struct json_object {
	struct json_kvp *value;                        //pointer to the first key/value pair that the object stores
} JSON_object;

//represents a primitive
typedef struct json_primitive {
	enum primitive_type type;                        //stores the type (bool, string, int). Does not support signed ints, floats, double, etc.
	void *value;                        //stores the primitive's value
} JSON_primitive;

//psudo parent class/generic type that keeps track of the json_member's name
//because array, object and primitive all have a member of type json_member, they can be cast to type json_member
typedef struct json_kvp { //key/value pair
	char *key;
	void *value;                        //points to json_array, json_object or json_primitive
} JSON_KVP;

//used for a linked list structure that stores everything in the JSON file
typedef struct json_node {
	struct json_kvp *value;
	struct json_node *next;
} JSON_node;
