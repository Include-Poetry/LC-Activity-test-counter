string citeFormat(){
	string year = "2020";
	string authors = "Velázquez R.";
	string version = "v0.5.1";

	string cite = "If you succesfully use this program please be so kind to cite:\n"
				+ authors + " (" + year + "). Activity test counter ("+ version +") [Computer software].\n"
				+ "Retrieved from https://github.com/Include-Poetry/LC-Activity-test-counter";

	return cite;
}