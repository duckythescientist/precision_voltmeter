
file = "precision_voltmeter-Eco1_User.svg";
ax = 20.64;
ay = 10.79;

offset_r = 0.23;
$fn=100;
difference() {
    translate([-110.48, -112.22, 0]) {
        union() {
            linear_extrude(12)
                offset(r=offset_r)
                    import(file);
            translate([0, 0, 4])
                hull()
                    linear_extrude(8)
                        offset(r=offset_r)
                            import(file);
        }
    }
    #scale([18.5/ax, 8.7/ay, 1 - 2/12])
    translate([-110.48, -112.22, 0]) {
        hull()
            linear_extrude(12)
                offset(r=offset_r)
                    import(file);
    }
}
