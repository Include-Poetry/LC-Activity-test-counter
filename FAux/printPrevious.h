void printPrevious(){
	cout << "    The following information has just been used:" << endl
		 << "    Date: " << ExpDia << '-' << ExpMes << '-' << ExpAno << endl
		 << "    Test performed: " << TipoExperimento;
	if (TipoExperimento == "TCS"){
		if(SIHabituacion){
			cout << " - (habituation)";
		} else {
			cout << " - (with stranger)";
		}
	}
	if (TipoExperimento == "ORT"){
		if(ORHabituacion){
			cout << " - (habituation)";
		} else {
			cout << " - (with novel object)";
		}
	}
	cout << endl
		 << "    Experiment duration " << FormatoReloj(TiempoRegis) << endl;

	if (!SoloDeltas){
		cout << "    Exit character: " << CharSalida << endl;
		if (TipoExperimento == "EPM"){
			cout << endl
				 << "    Position indicators" << endl
				 << "       " << PMOpen << " -> For open spaces" << endl
				 << "       " << PMCenter << " -> For central space" << endl
				 << "       " << PMClose << " -> For closed spaces" << endl;
		}
		if (TipoExperimento == "TCS"){
			cout << endl
				 << "    Activity and position indicators:" << endl
				 << "       " << SISpaceA << " -> For " << TipoEspacioA << endl
				 << "       " << SISpaceB << " -> For " << TipoEspacioB << endl
				 << "       " << SISpaceC << " -> For " << TipoEspacioC << endl
				 << "       " << SIGrooming << " -> For grooming" << endl
				 << "       " << SIInteract << " -> For interaction" << endl;
		}
		if (TipoExperimento == "ORT"){
			cout << endl
				 << "    Activity indicators: " << endl
				 << "       " << ORObjectA << " -> For " << TipoObjetoA << " object " << endl
				 << "       " << ORObjectB << " -> For " << TipoObjetoB << " object "  << endl
				 << "       " << ORGrooming << " -> For grooming" << endl;
		}
	}
	cout << endl;
	return;
}