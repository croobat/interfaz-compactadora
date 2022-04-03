//==================< Lift >=====================
void stateLift(){
    Serial.println("Levantar");
}

//-----< De Levantar a Alto >-----
bool transitionLiftHalt(){
    if (false && false) {
        // carrera cilindro > 0 & soltar botón levantar
        return true;
    }
    return false;
}

//-----< De Levantar a Inactivo >-----
bool transitionLiftIdle(){
    if (false) {
        // carrera cilindro = 0
        return true;
    }
    return false;
}

