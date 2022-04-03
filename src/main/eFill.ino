//==================< Fill >=====================
void stateFill(){
    Serial.println("Rellenar");
}

//-----< De Rellenar a Extraer >-----
bool transitionFillExtract(){
    if (false && false) {
        // Peso >= 20 kg & sensor magnético cerrado
        return true;
    }
    return false;
}

//-----< De Rellenar a Compactar >-----
bool transitionFillCompact(){
    if (false && false) {
        // Peso < 20 kg & pulsar botón compactar
        return true;
    }
    return false;
}

//-----< De Rellenar a Levantar >-----
bool transitionFillLift(){
     if (false && false) {
        // Peso < 20 kg & pulsar botón levantar
        return true;
    }
    return false;
}

