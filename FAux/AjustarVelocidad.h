void AjustarVelocidad(){
	cout << endl
		 << "    Enter the speed at which the register was made based on" << endl
		 << "    the playback speed you used." << endl
		 << "    If one minute of register equals to one minute of test" << endl
		 << "    then the speed is 1" << endl
		 << "    If the video was played two times faster, then the speed is 2" << endl
		 << "    If the video was played two times slower, then the speed is 0.5" << endl
		 << "    Speed of register: ";
	cin >> SpeedFactor;
	cout << endl;

	SpeedFactor = SpeedFactor > 0 ? SpeedFactor : SpeedFactor*-1;
	for (int i=0; i<TiemposCont; i++){
		registro[1][i] *= SpeedFactor;
	}
	return;
}