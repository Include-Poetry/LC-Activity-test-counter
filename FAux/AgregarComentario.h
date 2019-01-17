void AgregarComentario(){
	cout << endl
		 << "    Add a comment or observation about this register." << endl
		 << "    If you do not have any comments, just press 'enter'." << endl
		 << "    Do not use special characters such as accents." << endl
		 << "    This comment will be added to the final report." << endl
		 << "    >_ ";
	cin.ignore();
	getline(cin, Comentario);
	if (Comentario.size() == 0){
		Comentario = "- None -";
	}
	cout << endl;
	return;
}