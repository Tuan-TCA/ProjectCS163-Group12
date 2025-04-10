@echo off
echo ================================
echo Switching to 'demo' branch...
git checkout demo


echo ================================
echo Adding local changes...
git add .

echo ================================
echo Committing local changes...
git commit -m "Local update from personal machine" --allow-empty

echo ================================
echo Pushing to remote 'demo' branch...
git push origin demo

echo ================================
echo Done. Press any key to exit...
pause > nul
