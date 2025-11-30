#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (planet > totalPlanets) {
        return fuel;
    }
    
    if (fuel <= 0) {
        printf("Planet %d: Fuel exhausted! Cannot continue.\n", planet);
        return 0;
    }
    fuel = fuel - consumption;
    if (fuel <= 0) {
        printf("Planet %d: Fuel exhausted! Cannot continue.\n", planet);
        return 0;
    }
    fuel = fuel + recharge;
    if (planet % 4 == 0) {
        fuel = fuel + solarBonus;
    }
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int initialFuel, consumption, recharge, solarBonus, totalPlanets;
    
    printf("Enter initial fuel: ");
    scanf("%d", &initialFuel);
    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);
    printf("Enter gravitational recharge: ");
    scanf("%d", &recharge);
    printf("Enter solar bonus: ");
    scanf("%d", &solarBonus);
    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);
    
    printf("\nSpacecraft Journey Simulation:\n");
    int finalFuel = calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);
    
    if (finalFuel > 0) {
        printf("\nMission Successful! Spacecraft completed journey with %d fuel remaining.\n", finalFuel);
    } else {
        printf("\nMission Failed! Spacecraft could not complete the journey.\n");
    }
    
    return 0;
}