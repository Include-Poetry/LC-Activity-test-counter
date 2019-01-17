void setDuration(){
	cout << "    Enter the test duration" << endl
		 << "       Hours: ";
	cin >> TrHoras;
	cout << "       Minutes: ";
	cin >> TrMins;
	cout << "       Seconds: ";
	cin >> TrSegs;
	TiempoRegis = (TrHoras*3600000) + (TrMins*60000) + (TrSegs*1000);
	cout << endl;
	return;
}