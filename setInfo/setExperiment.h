void setExperiment(){
	cout << "    Enter the test to register" << endl
		 << "       [TST] -> Tail Suspension Test" << endl
		 << "       [FST] -> Forced Swim Test" << endl
		 << "       [HBT] -> Hole Board Test" << endl
		 << "       [EPM] -> Elevated Plus Maze" << endl
		 << "       [TCS] -> Three Chamber Sociability test" << endl
		 << "       [ORT] -> Object Recognition Test" << endl
		 << "    Choice: ";
	cin >> TipoExperimento;
	cout << endl;
	return;
}