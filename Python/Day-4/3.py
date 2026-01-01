def recommend_project(skill, interest):
    projects = [
        {"title": "Calculator App", "skill": "beginner", "interest": "python", "rating": 4.2},
        {"title": "To-Do List App", "skill": "beginner", "interest": "python", "rating": 4.5},
        {"title": "Weather App", "skill": "intermediate", "interest": "python", "rating": 4.6},
        {"title": "Portfolio Website", "skill": "beginner", "interest": "web", "rating": 4.3},
        {"title": "E-Commerce Website", "skill": "intermediate", "interest": "web", "rating": 4.7}
    ]

    best_project = None
    highest_rating = 0

    for project in projects:
        if project["skill"] == skill and project["interest"] == interest:
            if project["rating"] > highest_rating:
                highest_rating = project["rating"]
                best_project = project

    if best_project:
        print("Recommended Project:", best_project["title"])
        print("Rating:", best_project["rating"])
    else:
        print("No matching project found.")
        print("Please improve your skills before enrollment.")

skill_level = input("Enter skill level (beginner/intermediate): ").lower()
area = input("Enter area of interest (python/web): ").lower()

recommend_project(skill_level, area)
