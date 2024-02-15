// In App.js in a new project
import { useState } from 'react';
import * as React from 'react';
import { View, Text,StyleSheet,TouchableOpacity,Image } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import CircularProgress from 'react-native-circular-progress-indicator';

function HomeScreen() {
const Stack = createNativeStackNavigator();
const [value, setValue] = useState(0);
const profileImage = require('../assets/images/kemal.jpg');
  return (
    <View style={{flex:1}}>
      <View className="h-full w-full" style={{backgroundColor:'#c1e7e9'}}>
      <View style={styles.container}>
      <TouchableOpacity style={styles.profileContainer}> 
        <Image source={profileImage} style={styles.profileImage} />  
     </TouchableOpacity>
      <View>
        <Text style={{color:'black', fontWeight:'bold', marginLeft:8, fontSize:20,}}>User_Name</Text>
      </View>
      </View>
    <View className="pt-30" style={{alignItems: 'center', justifyContent: 'center' }}>  
      <CircularProgress
      radius={90}
      value={85}
      textColor='#222'
      fontSize={20}
      valueSuffix={'%'}
      inActiveStrokeColor={'#2ecc71'}
      inActiveStrokeOpacity={0.2}
      inActiveStrokeWidth={6}
      duration={3000}
      onAnimationComplete={() => setValue(50)}
      />
      <Text>Heart Rate</Text>
      <CircularProgress
      radius={90}
      value={85}
      textColor='#222'
      fontSize={20}
      valueSuffix={'%'}
      inActiveStrokeColor={'#2ecc71'}
      inActiveStrokeOpacity={0.2}
      inActiveStrokeWidth={6}
      duration={3000}
      onAnimationComplete={() => setValue(40)}
      />
      <Text>SpO2</Text>
      <CircularProgress
      radius={90}
      value={85}
      textColor='#222'
      fontSize={20}
      valueSuffix={'%'}
      inActiveStrokeColor={'#2ecc71'}
      inActiveStrokeOpacity={0.2}
      inActiveStrokeWidth={6}
      duration={3000}
      onAnimationComplete={() => setValue(60)}
      />
      <Text>Temperature</Text>
    </View>
    </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    alignItems: 'center',
    marginRight: 10,
    marginTop:50,
  },
  profileContainer: {
    width: 50,
    height: 50,
    borderRadius: 40, // half of the width and height to make it a circle
    overflow: 'hidden',
    marginLeft: 10,
  },
  profileImage: {
    width: '100%',
    height: '100%',
  },
  logoutContainer: {
    marginLeft: 250,
  },
  logoutIcon: {
    fontSize: 30,
    color: 'black',
  },
  semiCircle: {
    width: 200,
    height: 100,
    backgroundColor: '#3498db', // Change color as needed
    borderTopLeftRadius: 100,
    borderTopRightRadius: 100,
  },
});

export default HomeScreen;

