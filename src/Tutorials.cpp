#include "Tutorials.h"
#include <QMovie>
#include <QString>
#include <QDebug>

Tutorials::Tutorials()
{
    loadExercises();
}

void Tutorials::loadExercises()
{
    // Load GIFs and descriptions
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/cable-standing-chest-press.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/decline-crunch.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/dumbbell-Bent-over-Row.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/dumbbell-bicep-curl.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/dumbbell-front-squat.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/dumbbell-leg-curl.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/dumbbell-triceps-extension.gif"));
    exerciseGifs.append(new QMovie("C:/Users/LtWea/OneDrive/HonorsApp/Tutorials/lateral-raises.gif"));


    exerciseDescriptions.append("Standing Cable Chest Press: Position dual pulleys to chest height and select an appropriate weight. Stand a foot or two in front of the cables, holding one in each hand. You can stagger your stance for better stability. Position the upper arm at a 90 degree angle with the shoulder blades together. This will be your starting position. Keeping the rest of the body stationary, extend through the elbows to press the handles forward, drawing them together in front of you. Pause at the top of the motion, and return to the starting position.");
    exerciseDescriptions.append("Decline Crunch: Put a bench in a decline position. Start at around 30 degrees to see how it feels and go from there. Lie on the bench and secure your legs on the knee and ankle pads. With your back against the bench, bring your hands to the sides of your head and take a breath. Initiate the crunch by engaging your abs and using them to lift your torso toward your thighs. Raise your torso as you simultaneously crunch in for maximum abdominal engagement. Your chest should come near to your knees at the top position. Hold the top position for a moment and slowly lower your torso back to the starting position.");
    exerciseDescriptions.append("Dumbbell Bent Over Row: Holding a dumbbell in your left hand, kneel on a bench with your right knee and support your body with your right arm. The dumbbell should be hanging straight down, with your left arm almost fully extended. Exhale as you pull the dumbbell up to the side of your waist. Hold for a count of two. Inhale as you lower the dumbbell to the starting position. Repeat for the desired number of reps. Repeat with your right arm.");
    exerciseDescriptions.append("Dumbbell Bicep Curl: Grab a pair of dumbbells and bring them to your sides with your arms straight. Have your palms neutral (facing your thighs). Position your feet in a comfortable stance, bend your knees slightly, bring your shoulders back, and squeeze your glutes. Take a breath, engage your abs, and curl the dumbbells up as you gradually rotate your wrists out. Your palms should be facing back at the top position. Curl the dumbbells until your wrists are slightly higher than your elbows and pause for a moment. Lower the dumbbells slowly and rotate your wrists in.");
    exerciseDescriptions.append("Dumbbell Front Squat: Stand upright with your feet shoulder width apart, each hand holding a dumbbell in front of your chest, palms facing your body. Keeping your head up and shoulders locked down, sit your hips down while pushing your knees outward so they stay inline with your toes. Squat down until your hips are below the plane of your knees. If you don’t have enough flexibility to do this, squat as low as you can comfortably. Push through your heels back up to the starting position.");
    exerciseDescriptions.append("Dumbbell Leg Curl: Lie on your stomach on a 30-degree incline bench with your legs straight behind you and grasp the side of the bench for assistance. Clamp the dumbbell between your feet and lift your toes off the floor and curl your knees to engage your hamstring. Pause for a moment and then return to the start.");
    exerciseDescriptions.append("Dumbbell Triceps Extensions: Sit on a bench with your back straight. Clutch a dumbbell vertically with both hands at chest height, palms facing the ceiling. Brace your core and press the dumbbell overhead with your elbows facing forward. Keep your upper arms next to your ears as you flex your elbows to lower the dumbbell behind you until your forearms touch your biceps. Raise the dumbbell back to the starting position.");
    exerciseDescriptions.append("Lateral Raises: Stand with your feet shoulder-width apart, holding a dumbbell in each hand by your sides, palms facing inward. Engage your core muscles to maintain stability throughout the exercise. With a slight bend in your elbows, raise the dumbbells out to the sides until your arms are parallel to the floor. Keep your wrists straight, and avoid using momentum to lift the weights. Slowly lower the dumbbells back to the starting position under control.");

    // Store exercise names
    exerciseNames.append("Standing Cable Chest Press");
    exerciseNames.append("Decline Crunch");
    exerciseNames.append("Dumbbell Bent Over Row");
    exerciseNames.append("Dumbbell Bicep Curl");
    exerciseNames.append("Dumbbell Front Squat");
    exerciseNames.append("Dumbbell Leg Curl");
    exerciseNames.append("Dumbbell Triceps Extensions");
    exerciseNames.append("Lateral Raises");
}

QMovie* Tutorials::getExerciseGif(int index) const
{
    return exerciseGifs.at(index);  // Return the GIF for the selected exercise
}

QString Tutorials::getExerciseDescription(int index) const
{
    return exerciseDescriptions.at(index);  // Return the description for the selected exercise
}

QStringList Tutorials::getExerciseNames() const {
    return exerciseNames;
}
