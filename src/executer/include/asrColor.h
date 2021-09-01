class asrColor{
private:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

public:

	asrColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//getters
	uint8_t getColor(int component);

	//setters
	void setColors(int index, uint8_t value);
};
