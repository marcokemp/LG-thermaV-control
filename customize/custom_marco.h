
Customize::Customize() 
{
    water_hyst_pos = 4.0; //still to be replaced by LG modbus state if we find how to connect this
    water_hyst_neg = -4.0; //still to be replaced by LG modbus state if we find how to connect this
    max_stooklijn_correction_pos = 3.0;
    max_stooklijn_correction_neg = -5.0;
    base_stooklijn_flow = 30.0;

}

void Customize::custom_idle_behavior() {
    //implemented pump runs intermittently during idling
    
    //static bool pumptimer_switch = false;
    static int pumptimer = 0;
    //replace cooling switch behavior by statemachine DL
    //if(id(cooling_switch_number).state==1){
    //    ESP_LOGD("cooling or heating", "cooling on, resetting pumptimer for idle behavior");
    //    pumptimer = 4320;
    //}
    //if(id(cooling_switch_number).state==0){
    //    ESP_LOGD("cooling or heating", "cooling off, normal idle behavior");
    //
    
    if (pumptimer==0) {
        pumptimer = 4320;
        //pumptimer_switch = true;
    } else if(pumptimer<15) {
        //if (!pumptimer_switch) {
        //    pumptimer_switch = true;
            ESP_LOGD("pumptimer", "pump on for 5 minutes to circulate water & run pump");
            if(!id(modbus_enable_heat).state){
                id(modbus_enable_heat).turn_on();
            }
        //}
        //ESP_LOGD("pumptimer", "pump on");
        //id(modbus_enable_heat).turn_on();
        pumptimer--;
    } else {
        //if(pumptimer_switch) {
        //    pumptimer_switch=false;
            ESP_LOGD("pumptimer", "pump off for 23h55 minutes to save energy");
            if(id(modbus_enable_heat).state){
                id(modbus_enable_heat).turn_off();
            }
        //}
        //ESP_LOGD("pumptimer", "pump off");
        //id(modbus_enable_heat).turn_off();
        pumptimer--;
    }
}
