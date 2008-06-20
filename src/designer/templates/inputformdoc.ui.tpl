<!DOCTYPE UI><UI version="3.2" stdsetdef="1">
<class>Document</class>
<widget class="wDocument">
    <property name="name">
        <cstring>Document</cstring>
    </property>
    <property name="Id">
        <number>$$$id$$$</number>
    </property>	    
    <property name="Name">
        <cstring>$$$name$$$</cstring>
    </property>
    <property name="geometry">
        <rect>
            <x>0</x>
            <y>0</y>
            <width>500</width>
            <height>378</height>
        </rect>
    </property>
    <property name="caption">
        <string>$$$caption$$$</string>
    </property>

    <widget class="QLayoutWidget">
        <property name="name">
            <cstring>layout1</cstring>
        </property>
        <property name="geometry">
            <rect>
                <x>390</x>
                <y>10</y>
                <width>94</width>
                <height>355</height>
            </rect>
        </property>
        <vbox>
            <property name="name">
                <cstring>unnamed</cstring>
            </property>
            <widget class="wActionButton">
                <property name="name">
                    <cstring>conductButton</cstring>
                </property>
                <property name="text">
                    <string>Ok</string>
                </property>
                <property name="action">
                    <bool>true</bool>
                </property>
                <property name="actionUpdate">
                    <bool>true</bool>
                </property>
                <property name="actionTurnOn">
                    <bool>true</bool>
                </property>
                <property name="actionClose">
                    <bool>true</bool>
                </property>
                <property name="actionId">
                    <number>0</number>
                </property>
                <property name="script">
                    <bool>false</bool>
                </property>
            </widget>
            <widget class="wActionButton">
                <property name="name">
                    <cstring>closeButton</cstring>
                </property>
                <property name="text">
                    <string>Закрыть</string>
                </property>
                <property name="action">
                    <bool>true</bool>
                </property>
                <property name="actionUpdate">
                    <bool>false</bool>
                </property>
                <property name="actionTurnOn">
                    <bool>false</bool>
                </property>
                <property name="actionClose">
                    <bool>true</bool>
                </property>
                <property name="actionId">
                    <number>0</number>
                </property>
                <property name="script">
                    <bool>false</bool>
                </property>
            </widget>
            <widget class="wActionButton">
                <property name="name">
                    <cstring>printButton</cstring>
                </property>
                <property name="text">
                    <string>Печать</string>
                </property>
                <property name="action">
                    <bool>true</bool>
                </property>
                <property name="actionUpdate">
                    <bool>false</bool>
                </property>
                <property name="actionTurnOn">
                    <bool>false</bool>
                </property>
                <property name="actionClose">
                    <bool>false</bool>
                </property>
                <property name="actionId">
                    <number>0</number>
                </property>
                <property name="script">
                    <bool>false</bool>
                </property>
            </widget>
            <spacer>
                <property name="name">
                    <cstring>spacer1</cstring>
                </property>
                <property name="orientation">
                    <enum>Vertical</enum>
                </property>
                <property name="sizeType">
                    <enum>Expanding</enum>
                </property>
                <property name="sizeHint">
                    <size>
                        <width>26</width>
                        <height>141</height>
                    </size>
                </property>
            </spacer>
        </vbox>
    </widget>

</widget>
<toolbars>
</toolbars>
<layoutdefaults spacing="5" margin="5"/>
<includehints>
    <includehint>wdocument.h</includehint>
</includehints>
</UI>
