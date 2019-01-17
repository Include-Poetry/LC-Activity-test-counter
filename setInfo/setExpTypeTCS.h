void setExpTypeTCS(bool hab){
	if (hab){
		TipoEspacioA = "chamber A (left)  ", 
		TipoEspacioB = "chamber B (middle)", 
		TipoEspacioC = "chamber C (right) ";
	} else {
		TipoEspacioA = "chamber with stranger", 
		TipoEspacioB = "central chamber      ",
		TipoEspacioC = "empty chamber        ";
	}
	return;
}