import React from "react";
import { StatusBar } from "expo-status-bar";
import { StyleSheet,Text,View } from "react-native";
import { ProgressCircle } from "react-native-svg-charts";

export default function App() {
    return(
        <View>
        <Text>Avinash</Text>
        <ProgressCircle
                size={120}
                width={15}
                fill={100}
                tintColor="#00e0ff"
                onAnimationComplete={() => console.log('onAnimationComplete')}
                backgroundColor="#3d5875"/>
        </View>
    );
}