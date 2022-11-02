@startuml
skin rose
[*] -right-> Discharge
Discharge : EN_VBUS = 0
Discharge : EN_VSNS = 0
Discharge : EN_DISCH = 1


Charging : EN_VBUS = 1
Charging : EN_VSNS = 0
Charging : EN_DISCH = 0
Charging : Reading Isense1 by ADC periodicaly
Charging -up-> Discharge : Isense < xx mA


Discharge -right->  LiquidDetect : 98mS Timeout
state LiquidDetect {
  [*] -> PreSteps
  PreSteps -> PostSteps : 2ms Timeout
  PostSteps -up->  Discharge : No Device No Liquid (COMP_H/L = 01)\nor Liquid(COMP_H/L = 10)
  PostSteps -down-> Charging : Device with No Liquid\n(COMP_H/L = 11)
  PreSteps : EN_VBUS = 0
  PreSteps : EN_VSNS = 1
  PreSteps : EN_DISCH = 0
  PostSteps : Read COMP_H & COMP_L
  }

@enduml
