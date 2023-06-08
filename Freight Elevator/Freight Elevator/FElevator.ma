[top]
components : Ecall@Ecall Elevator
out : floor
in : inside_call
in : outside_call
Link : inside_call inside_call@Ecall
Link : outside_call outside_call@Ecall
Link : call_gen@Ecall acall@Elevator
Link : floor@Elevator floor


[Elevator]
components : Econtrol@Econtrol Evehicle@Evehicle
out : floor
in : acall
Link : timem@Econtrol in@Evehicle
Link : out@Evehicle fback@Econtrol
Link : floor@Econtrol floor
Link : acall acall@Econtrol
