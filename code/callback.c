typedef struct{
	int value;
	char *name;
}custom_data_t;

void callback(void *args){
	custom_data_t *data = (custom_data_t*)args;
	printf("Name: %s, value: %d\n", data->name, data->value);
}

int main(){
	custom_data_t data = {
		.value = 42,
		.name = "The answer"
	};
	
	register_callback(callback, &data);
}