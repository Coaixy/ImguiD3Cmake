class Flag
{
public:
	Flag();
	bool open;
	bool line;
	bool box;
	ImVec4 draw_color;
private:

};

Flag::Flag()
{
	this->open = false;
	this->line = false;
	this->box = false;
	this->draw_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}
static Flag flag;
