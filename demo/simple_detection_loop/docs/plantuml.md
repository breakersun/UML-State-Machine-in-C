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
Charging -up-> Discharge : Charging Stopped\nIsense < xx mA
Charging --> Charging : Charging in Progress\nIsense >= xx mA


Discharge -right->  LiquidDetect : 98mS Timeout
state LiquidDetect {
  [*] -> PreSteps
  PreSteps -> PostSteps : 2ms Timeout
  state COMP <<choice>>
  PostSteps -> COMP
  COMP -up->  Discharge : [COMP_H/L = 01;\nNo Deivce No Liquid]
  COMP -up->  Discharge : [COMP_H/L = 10;\nDevice + Liquid\nor just Liquid]
  COMP -up->  Discharge : [COMP_H/L = 00;\nShould Never Happen]
  COMP -down->  Charging : [COMP_H/L = 11;\nGood Device]
  PreSteps : EN_VBUS = 0
  PreSteps : EN_VSNS = 1
  PreSteps : EN_DISCH = 0
  PostSteps : Read:\nCOMP_H \nCOMP_L
}

@enduml
