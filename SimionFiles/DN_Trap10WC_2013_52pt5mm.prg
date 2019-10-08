;Modified for 8Li by MGS 11_11_09
;
;RF driving for practice paul trap
;July 1, 2009
;
;last modified July 20th 2009 - fixed the "switches" for groups and divided voltage in half
;
;This is the Simion user program for paul_practice.PA0 and paul_practice1.PA0
;it adds an RF voltage to the electrodes and a DC offset
;
;
;------------------------------------------------------
;definition of adjustable variables


; linear trap 6.5 segment + plate + einzel lens + cooling down to kT
; einzel lens adj_elect 01,02,03
; plate 		  "     04
; linear RFQ	  "     05-14, with odds one phase and even other phase
; DC biases on 5/6 and 9/10 for trap boundary, 7/8 for trap depth
; and 11/12 - 13/14 for slope
; proper cooling
;
; remodified April 18/2000 by GS to put trap in second rf
; sector and proper pulse out, RF on during ejection
;
; MODS AT 21:00, NO RF DURING EJECTION
; Guy Savard Nov. 31 1997
; more accurate collision model input in July, 2001
;
;Modified Oct. 7 2009 by Matt Sternberg
;improved gas collision model by allowing the distribution of
;of gas velocities sampled during collisions to account for the likelihood
;of collision over a time step based on the relative velocity between the
;ion and gas


; definition of user adjustable variables  -----------------------

		; ---------- lenght of simulation ----------------
defa run_length 		0.02		; length of run in msec (0 gives no limit)

		; ---------- adjustable during flight -----------------
defa _b_max 			7.0
defa _Percent_tune		0.0		; percent of optimum tune (DC voltage)
defs _AMU_Mass_per_Charge       137.0	  	; mass tune point in amu/unit charge
defs _Collision_Gas_Mass	4.0	  	; assume Helium


		; ---------- adjustable at beginning of flight -----------------

defa PE_Update_each_usec	0.005  		; pe surface update time step in usec
defa Percent_Energy_Variation   0.0   		; (+- 10%) random energy variation
defa Cone_Angle_Off_Vel_Axis	0.0   		; (+- 5 deg) cone angle - sphere
defa Random_Offset_mm		0.0   		; del start position (y,z) in mm
defa Random_TOB 		0.0   	; random time of birth over one cycle

;defa _P_region3_torr 		.00000000000001	  	; pressure in torr
defa _P_region3_torr 		.000001	  	; pressure in torr
defa gas_temp			273.0

; definition of static variables -----------------------------

defs Bolt_k			0.000086173423	; Boltzmann's k in eV/K
defs _mean_free_path 		0.0	  	; modified in subroutines

defs v_gas			1.0	  	; v_gas, from KE=3kT/2
defs v_eff			1.0
defs u_mass 			2.666666666	; m_ion*m_gas / ( m_ion + m_gas )
defs u_prime			0.666666666  	; u_mass / m_ion
defs u_pr2			0.333333333  	; u_mass / m_gas
defs theta_b			30.0	  	; scattering angle
defs el_ion_cm			0.0
defs az_ion_cm			0.0
defs v_ion_cm			0.0
defs ion_vxp_cm 		0.0
defs ion_vyp_cm 		0.0
defs ion_vzp_cm 		0.0
defs gas_vx_mm			0.0
defs gas_vy_mm			0.0
defs gas_vz_mm			0.0
defs vx_of_CM			0.0
defs vy_of_CM			0.0
defs vz_of_CM			0.0
defs ke_reaction		0.1
defs b_reaction 		7.0
defs A_coef 			1.0
defs B_coef 			1.0
defs D_coef 			1.0
defs A_vx			1.0		;our coeffs
defs B_vx			1.0
defs C_vx			1.0
defs A_vy			1.0
defs B_vy			1.0
defs C_vy			1.0
defs vx_flow		 	0.0
defs vy_flow		 	0.0
defs xval			0.00001
defs yval			0.00001
defs flow3d_x		 	0.0
defs flow3d_y		 	0.0
defs flow3d_z		 	0.0
defs Next_PE_Update 		0.0	  	; next time to update pe surface
defs kecutoff		  	0.1
defs vthermal			0.1
defs vgas_max			2		;max velocity of gas used in collisions (mm/mic-sec)
						;should scale with sqrt(T/77)

;-----RF variables-----

Defa RF_FreqA 0.310e6                                ;RF frequency in Hz for the 3 components
Defa RF_FreqB 0.620e6
Defa RF_FreqC 0.930e6

Defa rf_voltsA  109.3                                     ;Peak-to-peak RF voltage for the 3 components
Defa rf_voltsB  1.15
Defa rf_voltsC  -8.9

Defa thetaA  1.461                                           ;Phase offsets for the 3 components
Defa thetaB  1.840
Defa thetaC  1.945

;-----DC offsets ------                                 these will determine the DC offsets for each electrode
                                                       ;Electrodes 03 and 04 are the center of the trap

Defa A_offset    20                                  ;DC offset for group A electrodes --> was +45
Defa dc_offset01   0                                   ;DC offset for electrode 01 (used to vary mathieu parameter "a")
Defa dc_offset02   0                                   ;DC offset for electrode 02 (used to vary mathieu parameter "a")

Defa B_offset      -17                                   ;DC offset for group B electrodes --> was -18
Defa dc_offset03   0                                   ;DC offset for electrode 03 (used to vary mathieu parameter "a")
Defa dc_offset04   0                                   ;DC offset for electrode 04 (used to vary mathieu parameter "a")

Defa C_offset    20                                   ;DC offset for group C electrodes --> was +45
Defa dc_offset05   0                                   ;DC offset for electrode 05 (used to vary mathieu parameter "a")
Defa dc_offset06   0                                   ;DC offset for electrode 06 (used to vary mathieu parameter "a")

;-----Electrode switches-----                           here are defined variables that can turn electrode groupings on or off.
;                                                       They are factors multiplied by the final electrode voltage taking values of 1 or 0, 1 indicates on and 0 indicates off

Defa Elect_A 1                                         ;switch for electrode grouping A.  Default is on
Defa Elect_B 1                                         ;switch for electrode grouping B.  Default is on
Defa Elect_C 1                                         ;switch for electrode grouping C.  Default is on

; program segments below --------------------------------------------



;------------------------------------------------------------------------------------------------------------------
seg tstep_adjust				; keep time step <= 0.1 Usec
;------------------------------------------------------------------------------------------------------------------
	rcl _mean_free_path 0.01 *
	rcl v_eff / 0.1
	x>y rlup
	rcl ion_time_step
	x<y exit
	rlup
	sto ion_time_step


;------------------------------------------------------
Seg Fast_Adjust                                        ;fast adjust segment to run RF
;------------------------------------------------------

      RCL RF_FreqA
      -6 10^X
      *                                                ;change frequency in Hz into cycles/microsec
      6.28319 *                                        ;change to angular frequency in rad/microsec
      STO omega_A                                        ;store as omega

      RCL Ion_time_of_Flight                           ;recall Ion TOF
      RCL thetaA                                        ;recall time offset
      -                                                ;(omega*TOF)
      RCL omega_A                                        ;recall frequency omega
      *                                                ;add phase factor ((omega*TOF)+theta)
      Sin                                              ;Sin[(omega*(TOF-theta)]
      RCL rf_voltsA                                     ;recall AC voltage
      *                                               
      STO tempvolts_A                                    ;store tempvolts=(rf_volts)*Sin[(omega*TOF)+theta]

      RCL RF_FreqB
      -6 10^X
      *                                                ;change frequency in Hz into cycles/microsec
      6.28319 *                                        ;change to angular frequency in rad/microsec
      STO omega_B                                        ;store as omega

      RCL Ion_time_of_Flight                            ;recall Ion TOF
      RCL thetaB                                        ;recall time offset
      -                                                ;(omega*TOF)
      RCL omega_B                                        ;recall frequency omega
      *                                                ;add phase factor ((omega*TOF)+theta)
      Sin                                              ;Sin[(omega*(TOF-theta)]
      RCL rf_voltsB                                     ;recall AC voltage
      *                                                 
      STO tempvolts_B                                    ;store tempvolts=(rf_volts)*Sin[(omega*TOF)+theta]

      RCL RF_FreqC
      -6 10^X
      *                                                ;change frequency in Hz into cycles/microsec
      6.28319 *                                        ;change to angular frequency in rad/microsec
      STO omega_C                                        ;store as omega

      RCL Ion_time_of_Flight                           ;recall Ion TOF
      RCL thetaC                                        ;recall time offset
      -                                                ;(omega*TOF)
      RCL omega_C                                        ;recall frequency omega
      *                                                ;add phase factor ((omega*TOF)+theta)
      Sin                                              ;Sin[(omega*(TOF-theta)]
      RCL rf_voltsC                                     ;recall AC voltage
      *                            
      STO tempvolts_C                                    ;store tempvolts=(rf_volts)*Sin[(omega*TOF)+theta]

      RCL tempvolts_A
      RCL tempvolts_B
      +
      RCL tempvolts_C
      +
      STO tempvolts

      -1 *
      STO tempvoltsminus     


;---- setting electrode voltages ----                   these will be of the form DC+U+Vsin(omega*TOF+theta) where U is the DC offset of the electrode and V is the AC voltage
;                                                       the parameter U (of the form dc_offset0*) is used to change the DC voltage of the electrodewith respect to the other in the same group, 
;                                                       The parameter DC is the offset of the grouping which will be used to create a longitudinal trapping potential

;-----group A ------

      RCL dc_offset01                                  ;recall DC_offset for electrode 01
      RCL A_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_A *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvolts                                    ;recall tempvolts
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect01                                  ;set electrode 01

      RCL dc_offset02                                  ;recall DC_offset for electrode 02
      RCL A_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_A *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvoltsminus                                    ;recall tempvoltsminus
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect02                                  ;set electrode 02

;-----group B ------

      RCL dc_offset03                                  ;recall DC_offset for electrode 03
      RCL B_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_B *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvolts                                    ;recall tempvolts
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect03                                  ;set electrode 03

      RCL dc_offset04                                  ;recall DC_offset for electrode 04
      RCL B_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_B *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvoltsminus                                    ;recall tempvoltsminus
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect04                                  ;set electrode 04

;-----group C ------


      RCL dc_offset05                                  ;recall DC_offset for electrode 05
      RCL C_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_C *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvolts                                    ;recall tempvolts
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect05                                  ;set electrode 05

      RCL dc_offset06                                  ;recall DC_offset for electrode 06
      RCL C_offset                                     ;recall DC offset for the group A
      +                                                ;evaluate DC+U+VSin(omega*TOF+theta)
      RCL Elect_C *                                    ;multiply by electrode switch value 1->on 0->0ff
      RCL tempvoltsminus                                    ;recall tempvolts
      +                                                ;evaluate (offset)+Vsin(omega*TOF+theta)
      STO Adj_Elect06                                  ;set electrode 06


;------------------------------------------------------------------------------------------------------------------
seg Other_Actions				; used to control pe surface updates
;------------------------------------------------------------------------------------------------------------------

;;	rcl ion_vz_mm				; mean free path cooling
;;	rcl ion_vy_mm				; load velocity vectors
;;	rcl ion_vx_mm
;;	>p3d					; convert velocity to polar coords
;;	sto v					; save in temporary variables
;;	rlup sto az
;;	rlup sto el



	rcl run_length 1000 *
	x=0 gto skp_run_length
	rcl ion_time_of_flight
	x>y gto kill


	lbl skp_run_length





	rcl ion_px_mm			   	;getting ion's position and converting
						;to gas cooler parameters
	sto xval

	rcl ion_py_mm
	entr *
	rcl ion_pz_mm
	entr *
	+ sqrt
	sto yval			  	;yval=sqrt(py^2+pz^2)




						;calculating vx_flow, vy_flow
	rcl vx_flow
	sto flow3d_x
	rcl ion_py_mm
	x!=0 gsb calc_vy
	rcl ion_py_mm
	x=0 gsb calc_vy0

	rcl Bolt_k
	rcl gas_temp
	*
	1.273239544735
	*
	rcl _collision_gas_mass			;ke= 3/2 kT
	x><y
	>spd					;converts ke(eV) to speed(mm/usec)
	sto vmean_gas

	

	rcl ion_vz_mm
	rcl flow3d_z -
	rcl ion_vy_mm
	rcl flow3d_y -
	rcl ion_vx_mm
	rcl flow3d_x -
	>P3D
	sto vion
	rlup sto az_ion
	rlup chs 1.570796327 + sto el_ion
	rldn rldn entr *
	rcl vmean_gas * +
	sqrt					;v_eff = sqrt( (v_ion_i-v_flow_i)^2 + v_gas^2)
	sto v_eff					;for i=x,y,z




	0.000067			; _mean_free_path[mm]=0.00067*T[K]/P[torr] for He with d=0.22nm
					;should be 0.0000016 for r=7 angstroms
	rcl gas_temp
	*
	rcl _P_region3_torr /
	sto _mean_free_path



	rcl v_eff
	rcl ion_time_step * 			; compute distance from tstep * v_eff
	rcl _mean_free_path / chs e^x
	1 x<>y -				;(1-e(-d/fp))
	rand					;get random number from 0 - 1
	x>y goto skip1				; no collision

						; collision (random angle v_gas and
						; fitted potential)


	lbl new_collision_pars

	rcl gas_temp 77 / sqrt
	rcl vgas_max *
	rand *	
	sto vgas
	rand 3.14159265358979 *
	sto el_gas

	cos *
	rcl vion *
	-2 *
	rcl vion entr * +
	rcl vgas entr * +
	sqrt
	rcl ion_time_step *
	rcl _mean_free_path / chs e^x
	chs 1 +

	rcl vgas entr * *
	rcl _collision_gas_mass
	rcl vgas
	>KE
	x<>y rlup
	rcl Bolt_k
	rcl gas_temp * /
	chs e^x *
	rcl el_gas sin *

	
	rcl vion entr *
	rcl vmean_gas entr * +
	sqrt
	rcl ion_time_step *
	rcl _mean_free_path / chs e^x
	chs 1 +
	1.1 *

	rcl vmean_gas entr * *
	rcl _collision_gas_mass
	rcl vmean_gas
	>KE
	x<>y rlup
	rcl Bolt_k
	rcl gas_temp * /
	chs e^x * /

	rand x>y gto new_collision_pars



	rand 6.2831853072 *
	sto az_gas

	cos
	rcl el_gas sin *
	rcl vgas *
	sto vx_gas_ion_ref			;vx of gas where y-axis is defined along vion

	rcl az_gas
	sin
	rcl el_gas sin *
	rcl vgas *
	sto vz_gas_ion_ref			;vz of gas where y-axis is defined along vion

	rcl el_gas cos
	rcl vgas *
	sto vy_gas_ion_ref			;vy of gas where y-axis is defined along vion

	rcl el_ion cos *
	rcl el_ion sin
	rcl vx_gas_ion_ref chs * +
	sto gas_vy_mm

	rcl el_ion cos
	rcl vx_gas_ion_ref *
	rcl el_ion sin
	rcl vy_gas_ion_ref * +
	rcl az_ion cos *
	rcl az_ion sin
	rcl vz_gas_ion_ref * +
	sto gas_vx_mm

	rcl el_ion cos
	rcl vx_gas_ion_ref *
	rcl el_ion sin
	rcl vy_gas_ion_ref * +
	rcl az_ion sin chs *
	rcl az_ion cos
	rcl vz_gas_ion_ref * +
	sto gas_vz_mm







	rcl gas_vx_mm				;combining flow3d with gas_v_mm
	rcl flow3d_x +
	sto gas_vx_mm
	rcl gas_vy_mm
	rcl flow3d_y +
	sto gas_vy_mm
	rcl gas_vz_mm
	rcl flow3d_z +
	sto gas_vz_mm

	rcl ion_vz_mm				; get ion's specified velocity components
	-
	chs
	rcl u_prime *
	rcl ion_vy_mm
	rcl gas_vy_mm
	-
	rcl u_prime *
	rcl ion_vx_mm
	rcl gas_vx_mm
	-
	rcl u_prime *
	>p3d
	sto v_ion_cm rlup			; store ion's cm speed
	sto az_ion_cm rlup			; store ion's az cm angle
	sto el_ion_cm				; store ion's el cm angle

	rcl ion_vz_mm
	rcl u_pr2 *
	rcl gas_vz_mm
	rcl u_prime *
	+
	sto vz_of_CM
	rcl ion_vy_mm
	rcl u_pr2 *
	rcl gas_vy_mm
	rcl u_prime *
	+
	sto vy_of_CM
	rcl ion_vx_mm
	rcl u_pr2 *
	rcl gas_vx_mm
	rcl u_prime *
	+
	sto vx_of_CM

	  >p3d


;;	  sto v_cm rlup 			; store cm speed
;;	  sto az_cm rlup			; store cm az angle
;;	  sto el_cm 				; store cm el angle

; -------------------------------------------------------
	rcl u_mass
	rcl v_ion_cm
	rcl u_prime
	/
	>KE
	sto ke_reaction
	rcl _b_max
	rand
	sqrt  *
	sto b_reaction
						; determine theta_b(b,E)
	1.133135046
	rcl ke_reaction
	/  sto B_coef
	-44.58807151
	rcl ke_reaction
	*
	E^X
	-0.3271660443 *
	0.4253543674 +
	sto A_coef
	9.146953914
	300.
	rcl ke_reaction
	*  1.578944559	+
	/
	2.819901970  +
	sto D_coef

	rcl b_reaction
	entr   *
	rcl A_coef
	chs  *
	E^X
	180  *
	rcl b_reaction
	rcl D_coef
	-
	entr  *
	-2.473046186	*
	E^X
	rcl B_coef
	*
	-
	sto theta_b 				; scattering angle
; -------------------------------------------------------

	90
	rcl theta_b -
	rand
	360 * 180 -
	rcl v_ion_cm
	>r3d
	-90
	>elr
	rcl el_ion_cm
	>elr
	rcl az_ion_cm
	>azr
	sto ion_vxp_cm				; return v_ion in CM after collision
	rlup
	sto ion_vyp_cm				; return v_ion in CM after collision
	rlup
	sto ion_vzp_cm				; return v_ion in CM after collision
	rcl vz_of_CM
	+
	sto ion_vz_mm
	rcl ion_vyp_cm
	rcl vy_of_CM
	+
	sto ion_vy_mm
	rcl ion_vxp_cm
	rcl vx_of_CM
	+
	sto ion_vx_mm



lbl skip1

	rcl Next_PE_Update			; recall time for next pe surface update
	rcl ion_time_of_flight			; recall ion's time of flight
	x<y exit				; exit if tof less than next pe update
	rcl PE_Update_each_usec 		; recall pe update increment
	+ sto next_pe_update			; add to tof and store as next pe update
	1 sto Update_PE_Surface 		; request a pe surface update
	goto end



lbl calc_vy 					;changing vy_flow into flow3d_y and flow3d_z
	rcl vy_flow
	rcl ion_py_mm *
	rcl ion_py_mm
	entr *
	rcl ion_pz_mm
	entr * +
	sqrt /
	sto flow3d_y
	rcl vy_flow
	rcl ion_pz_mm *
	rcl ion_py_mm
	entr *
	rcl ion_pz_mm
	entr * +
	sqrt /
	sto flow3d_z

rtn

lbl calc_vy0
	0.0
	sto flow3d_y
	rcl vy_flow
	sto flow3d_z
rtn


lbl kill
	-4
	sto Ion_Splat

lbl end



;----------------------------------------------------------------------------------------------------------------
seg Terminate
;----------------------------------------------------------------------------------------------------------------
			0 sto rerun_flym	; turn off rerun mode

;end of program

