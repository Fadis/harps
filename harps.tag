<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="namespace">
    <name>harps</name>
    <filename>namespaceharps.html</filename>
    <class kind="class">harps::Buffer</class>
    <class kind="class">harps::ClockMatrixCalc</class>
    <class kind="class">harps::ClockMatrixCalc&lt; LOCAL &gt;</class>
    <class kind="class">harps::ClockMatrixCalc&lt; KEY &gt;</class>
    <class kind="class">harps::ClockMatrixCalc&lt; TONE &gt;</class>
    <class kind="class">harps::CurrentTime</class>
    <class kind="class">harps::Clock</class>
    <class kind="class">harps::DynamicModuleSocket</class>
    <class kind="class">harps::DynamicModuleSlot</class>
    <class kind="class">harps::Dummy</class>
    <class kind="class">harps::HarpsException</class>
    <class kind="class">harps::ModuleNotFound</class>
    <class kind="class">harps::UnableToCreateInstance</class>
    <class kind="class">harps::UnableToOpenSink</class>
    <class kind="class">harps::SinkConfigurationFailed</class>
    <class kind="class">harps::SinkOutputFailed</class>
    <class kind="class">harps::DynamicMonophony</class>
    <class kind="class">harps::DynamicPolyphony</class>
    <class kind="class">harps::Normalizer</class>
    <class kind="class">harps::Note</class>
    <class kind="class">harps::SharedBuffer</class>
    <namespace>harps::compornent</namespace>
    <namespace>harps::input</namespace>
    <namespace>harps::output</namespace>
    <member kind="typedef">
      <type>double</type>
      <name>Time</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>e436698398d387e2b89ecdc95171e7a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; Time, Time &gt;</type>
      <name>TimeMatrix</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>e9707f612d7e353030e63165bc8796fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>noteToFrequency</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>4f7bddae87173a07222e7cd4b32519bb</anchor>
      <arglist>(float _note)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>getModulePath</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>39a98007c1da8f7aedcfe13c51760124</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reduceNormalizingNoize</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>9f18f91c4acdcbfe42895fc812853066</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getTime</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>54146ea57c1846a470bf191f51516988</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sleep</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>7ddb3dd742346b37c7027671e7878792</anchor>
      <arglist>(double _until)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>loop</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>87cb95178359fc94fd9cf4b8c6bcefff</anchor>
      <arglist>(float _source)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>loop</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>cb6eb6b6be744624501519370f1973ed</anchor>
      <arglist>(double _source)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>sin</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>14925ee15691035e1d0e8c9efbc73c0d</anchor>
      <arglist>(float _theta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>sin</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>4286fc6aa658faf13aaa83d4d2402a4e</anchor>
      <arglist>(double _theta)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>volume</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>2d3449b08861e19e466414aed28d4f22</anchor>
      <arglist>(float _linear)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>volume</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>561f42a6eddee3829c8e429b1209fc7e</anchor>
      <arglist>(double _linear)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>triangle</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>521c0226ca004e6f0942eebbcd706fb0</anchor>
      <arglist>(float _theta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>triangle</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>59471afc6a4b9fda2abad9ef125c6245</anchor>
      <arglist>(double _theta)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>rectangle</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>ec41e89fe7065da3484b8e541bdd42a1</anchor>
      <arglist>(float _duty, float _theta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>rectangle</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>77bf2d30984c1216bd4809e722675683</anchor>
      <arglist>(double _duty, double _theta)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>nes</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>99acf61c717498656a088ceb0c6d8e3e</anchor>
      <arglist>(float _theta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>nes</name>
      <anchorfile>namespaceharps.html</anchorfile>
      <anchor>bebd9a61b530b183652b2d08e2e8ee23</anchor>
      <arglist>(double _theta)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::Buffer</name>
    <filename>classharps_1_1Buffer.html</filename>
    <templarg>_SampleType</templarg>
    <member kind="typedef">
      <type>_SampleType</type>
      <name>SampleType</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>f7833b35eca516673a6673a2e3891de9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Buffer</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>efec369ca2232f71a3846085fee8eb93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Buffer</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>31d11f5c708d11688b49bee7e9af84fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SampleType *</type>
      <name>get</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>2a7f5913399484eec854689812ea0bb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SampleType *</type>
      <name>getLeft</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>6050133c6cd1ab3db1c7a169633dddf4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>SampleType *</type>
      <name>getRight</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>668b1ac5c2af479da54a29cbec5a55c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const SampleType *</type>
      <name>get</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>97753c5714688c1be48ab451be12da34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const SampleType *</type>
      <name>getLeft</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>1172c500abe58b618a8a765cef5b9189</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const SampleType *</type>
      <name>getRight</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>17f18647a15e3ec85c4e6e497e2639f2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStereo</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>5b03fbc0c2d1a6cede5a3c8a6d08aff9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMonoral</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>d64ce748ee70aaf027e30bc4ac23a641</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isStereo</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>aed1f9feac43f2110bc0345847259a2f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>requestContinue</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>c8c59a4b9026ae0db6029846305dfdb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>requestEnd</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>0975021873c9957e22944e210d0a6de9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>5c9522a1c6d2f36bfb387fc4ee1832fb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>shouldEnd</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>559084a4b5a2932f04a00aefe3cb7e37</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mergeVote</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>a42515d3024bfe66b2aea07e21e09e01</anchor>
      <arglist>(const Buffer&lt; _SampleType &gt; &amp;_source)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getContinueRequestCount</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>f102d36b2f325b5d22fa91b7dfb6d7ba</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>getEndRequestCount</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>588439f2fb486c1ceef8f3e2700e1110</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setUsed</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>cb84b61718acf55369f9d896db08649b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getUsed</name>
      <anchorfile>classharps_1_1Buffer.html</anchorfile>
      <anchor>7d71d808b95592e23858926cc6fec561</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::ClockMatrixCalc</name>
    <filename>classharps_1_1ClockMatrixCalc.html</filename>
    <templarg>_which</templarg>
  </compound>
  <compound kind="class">
    <name>harps::ClockMatrixCalc&lt; LOCAL &gt;</name>
    <filename>classharps_1_1ClockMatrixCalc_3_01LOCAL_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>updateCache</name>
      <anchorfile>classharps_1_1ClockMatrixCalc_3_01LOCAL_01_4.html</anchorfile>
      <anchor>5af09ed3058237c047d95665d3cc40f2</anchor>
      <arglist>(TimeMatrix *_cache, TimeMatrix *_coef)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::ClockMatrixCalc&lt; KEY &gt;</name>
    <filename>classharps_1_1ClockMatrixCalc_3_01KEY_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>updateCache</name>
      <anchorfile>classharps_1_1ClockMatrixCalc_3_01KEY_01_4.html</anchorfile>
      <anchor>e156e5b3173bbeab94687aa4a4262bac</anchor>
      <arglist>(TimeMatrix *_cache, TimeMatrix *_coef)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::ClockMatrixCalc&lt; TONE &gt;</name>
    <filename>classharps_1_1ClockMatrixCalc_3_01TONE_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>updateCache</name>
      <anchorfile>classharps_1_1ClockMatrixCalc_3_01TONE_01_4.html</anchorfile>
      <anchor>1cf69a43c67340a4dace57cf6e15a7e4</anchor>
      <arglist>(TimeMatrix *_cache, TimeMatrix *_coef)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::CurrentTime</name>
    <filename>classharps_1_1CurrentTime.html</filename>
    <member kind="function">
      <type></type>
      <name>CurrentTime</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>6a58e37c3b82280888f7d39e9387fda9</anchor>
      <arglist>(Time _tick_length)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getTime</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>b4e5c08585a7599b89db2dac14b9c4d1</anchor>
      <arglist>(unsigned int _offset) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>74647316ea9eed4d83fe899b18d110a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>swapMatrix</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>28f0470f31805494343847286d69694e</anchor>
      <arglist>(TimeMatrix &amp;_matrix)</arglist>
    </member>
    <member kind="function">
      <type>const TimeMatrix &amp;</type>
      <name>getMatrix</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>b7d1435e1b3d59c6a71b6d85c3743d3c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOn</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>17506ab95e4f9dd773489478751f39d4</anchor>
      <arglist>(int _note)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOff</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>d4ba06019a3066b8aa29bb3a789d9e5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPitchBend</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>1cf8a7b0fb4fde33e472acf9d086816d</anchor>
      <arglist>(float _pitch)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getToneFrequency</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>3fbbd98cbd3c4517bbf49e62d86f2cc5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getTone</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>3f08fd579a5b04db6ceb2497984d237b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getPitchBend</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>4843be872283108748b222eebefec0c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tick</name>
      <anchorfile>classharps_1_1CurrentTime.html</anchorfile>
      <anchor>4997fde13ba0065725222565dedc6321</anchor>
      <arglist>(unsigned int _sample_count)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::Clock</name>
    <filename>classharps_1_1Clock.html</filename>
    <templarg>_sampling_rate</templarg>
    <templarg>_sample_count</templarg>
    <base>harps::CurrentTime</base>
    <member kind="function">
      <type>void</type>
      <name>tick</name>
      <anchorfile>classharps_1_1Clock.html</anchorfile>
      <anchor>39971acf3b3d864c1e3484ee055d93ef</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::DynamicModuleSocket</name>
    <filename>classharps_1_1DynamicModuleSocket.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicModuleSocket.html</anchorfile>
      <anchor>a127ba795c508bf5981cb2d6fab79f07</anchor>
      <arglist>(Buffer&lt; float &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicModuleSocket.html</anchorfile>
      <anchor>87cba2d094ec5fc6b6d1f20502158829</anchor>
      <arglist>(Buffer&lt; double &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::DynamicModuleSlot</name>
    <filename>classharps_1_1DynamicModuleSlot.html</filename>
    <member kind="function">
      <type></type>
      <name>DynamicModuleSlot</name>
      <anchorfile>classharps_1_1DynamicModuleSlot.html</anchorfile>
      <anchor>ae856e3f338981e6016c9834433bfeff</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicModuleSlot.html</anchorfile>
      <anchor>0bb30450af88f9a6bfe7b796d6533a05</anchor>
      <arglist>(Buffer&lt; float &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicModuleSlot.html</anchorfile>
      <anchor>d8a9c601e21e7daf79992b65e6babb36</anchor>
      <arglist>(Buffer&lt; double &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::HarpsException</name>
    <filename>classharps_1_1HarpsException.html</filename>
    <member kind="function">
      <type></type>
      <name>HarpsException</name>
      <anchorfile>classharps_1_1HarpsException.html</anchorfile>
      <anchor>1c1c3000d2e0184cbeedb07d13c80eb4</anchor>
      <arglist>(const char *_value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::ModuleNotFound</name>
    <filename>classharps_1_1ModuleNotFound.html</filename>
    <base>harps::HarpsException</base>
  </compound>
  <compound kind="class">
    <name>harps::UnableToCreateInstance</name>
    <filename>classharps_1_1UnableToCreateInstance.html</filename>
    <base>harps::HarpsException</base>
  </compound>
  <compound kind="class">
    <name>harps::UnableToOpenSink</name>
    <filename>classharps_1_1UnableToOpenSink.html</filename>
    <base>harps::HarpsException</base>
  </compound>
  <compound kind="class">
    <name>harps::SinkConfigurationFailed</name>
    <filename>classharps_1_1SinkConfigurationFailed.html</filename>
    <base>harps::HarpsException</base>
  </compound>
  <compound kind="class">
    <name>harps::SinkOutputFailed</name>
    <filename>classharps_1_1SinkOutputFailed.html</filename>
    <base>harps::HarpsException</base>
  </compound>
  <compound kind="class">
    <name>harps::DynamicMonophony</name>
    <filename>classharps_1_1DynamicMonophony.html</filename>
    <member kind="function">
      <type></type>
      <name>DynamicMonophony</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>1aa6282a44718f26647c48aa627a80f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>034e8a8eb8d8fafd8df36379fb1647dc</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>noteOn</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>183d62c092e5903c0e60b5ded5670290</anchor>
      <arglist>(int _note, float _touch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOff</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>46144634cfb0eefe21660fdf5ac3baef</anchor>
      <arglist>(int _dummy=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteWait</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>25728aacf3836d4e1fe4e401b02021df</anchor>
      <arglist>(int _dummy=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPitchBend</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>4d304ca1400cb443cdb57a17cdedb3db</anchor>
      <arglist>(float _pitch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>9293fc3cfa3044994c65a06c0e5709dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Note::NoteState</type>
      <name>getStatus</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>7691d2caaed5a624a33541a6c89f62a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getGlobalTime</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>5891615a1418f7d7636469594c216f62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>programChange</name>
      <anchorfile>classharps_1_1DynamicMonophony.html</anchorfile>
      <anchor>1906e8848e676602585df3f896166dca</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::DynamicPolyphony</name>
    <filename>classharps_1_1DynamicPolyphony.html</filename>
    <templarg>MonophonyType</templarg>
    <templarg>max_polyphony</templarg>
    <member kind="function">
      <type></type>
      <name>DynamicPolyphony</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>c15bc693840c9fee92b45a46c61db43d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>3a2597029685d470e88e32a2ce3db94a</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>noteOn</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>664216adf59bb943e5e399c43309888c</anchor>
      <arglist>(int _note, float _touch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOff</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>7accc347e968a411ecaf81b377a5e50f</anchor>
      <arglist>(int _note_id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPitchBend</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>d150e720cad12009a12982f0b467a707</anchor>
      <arglist>(int _note_id, float _pitch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPitchBend</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>c6e407d71432eec1425e56a5e5461f86</anchor>
      <arglist>(float _pitch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>a719ce61a5f7c106a8bcc896b9a5c167</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>findMonophony</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>0db5c94c16f5babf60c2e47d02cb6f36</anchor>
      <arglist>(int _note_id)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>getGlobalTime</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>04c6b1c548270bc160e7a96e6ecc034d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>programChange</name>
      <anchorfile>classharps_1_1DynamicPolyphony.html</anchorfile>
      <anchor>1223aecd5a7ee1bcbf22904cb555ab50</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
    <class kind="class">harps::DynamicPolyphony::Renderer</class>
  </compound>
  <compound kind="class">
    <name>harps::Normalizer</name>
    <filename>classharps_1_1Normalizer.html</filename>
    <templarg>tail</templarg>
    <member kind="function">
      <type></type>
      <name>Normalizer</name>
      <anchorfile>classharps_1_1Normalizer.html</anchorfile>
      <anchor>fa7525284211f02baf449163696400b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classharps_1_1Normalizer.html</anchorfile>
      <anchor>719c26a532ee603de347033951b9e7ba</anchor>
      <arglist>(float _arg_value)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getAmp</name>
      <anchorfile>classharps_1_1Normalizer.html</anchorfile>
      <anchor>b4d4314f348404d2e96d2d22b3f1ced7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::Note</name>
    <filename>classharps_1_1Note.html</filename>
    <member kind="function">
      <type></type>
      <name>Note</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>e30d3c03bff9e694ce939e0e5c62212b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOn</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>f589da8cf6f57aa65d484909bb1eb61b</anchor>
      <arglist>(float _touch=1.0f)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteOff</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>99f66a9ff92dd3ad30199816c455fa78</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>noteWait</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>ae555fa8b846740ece16309eeb3aed89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>NoteState</type>
      <name>getStatus</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>2e242ce9707561f3ff22f9d61ecf332a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>getTouch</name>
      <anchorfile>classharps_1_1Note.html</anchorfile>
      <anchor>4c5924cbd850f3221114a24872be5f83</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::SharedBuffer</name>
    <filename>classharps_1_1SharedBuffer.html</filename>
    <templarg>Tag</templarg>
    <templarg>SampleType</templarg>
    <templarg>count</templarg>
    <member kind="function" static="yes">
      <type>static boost::array&lt; SampleType, count &gt; &amp;</type>
      <name>init</name>
      <anchorfile>classharps_1_1SharedBuffer.html</anchorfile>
      <anchor>ca645777b94d527a7e340aba24b2c104</anchor>
      <arglist>(boost::function&lt; void(boost::array&lt; SampleType, count &gt; &amp;) &gt; _initializer)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>harps::compornent</name>
    <filename>namespaceharps_1_1compornent.html</filename>
    <class kind="class">harps::compornent::Add</class>
    <class kind="class">harps::compornent::Add&lt;  &gt;</class>
    <class kind="class">harps::compornent::BranchByNote</class>
    <class kind="class">harps::compornent::Constant</class>
    <class kind="class">harps::compornent::ConstantMul</class>
    <class kind="class">harps::compornent::Distotion</class>
    <class kind="class">harps::compornent::Envelope</class>
    <class kind="class">harps::compornent::Envelope&lt; _clock_select, _delay, _attack, _hold, _decay, 0, _release &gt;</class>
    <class kind="class">harps::compornent::Envelope2</class>
    <class kind="class">harps::compornent::Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, 0, _release, _release_middle, _release_middle_level &gt;</class>
    <class kind="class">harps::compornent::FM</class>
    <class kind="class">harps::compornent::FM&lt; ModuleType0, ModuleType1, 0, 0, 0, 0, 0, 0, 0 &gt;</class>
    <class kind="class">harps::compornent::FM2</class>
    <class kind="class">harps::compornent::Generator</class>
    <class kind="class">harps::compornent::Mix</class>
    <class kind="class">harps::compornent::Mix&lt;  &gt;</class>
    <class kind="class">harps::compornent::Mul</class>
    <class kind="class">harps::compornent::Mul&lt;  &gt;</class>
    <class kind="class">harps::compornent::FFT</class>
    <class kind="class">harps::compornent::Noize</class>
    <class kind="class">harps::compornent::Normalize</class>
    <class kind="class">harps::compornent::Rectangle</class>
    <class kind="class">harps::compornent::Scale</class>
    <class kind="class">harps::compornent::Scale&lt; ModuleType, 1000, 0 &gt;</class>
    <class kind="class">harps::compornent::Shift</class>
    <class kind="class">harps::compornent::Sine</class>
    <class kind="class">harps::compornent::SwitchingEnvelope</class>
    <class kind="class">harps::compornent::Touch</class>
    <class kind="class">harps::compornent::Triangle</class>
    <class kind="class">harps::compornent::NES</class>
    <class kind="class">harps::compornent::Vector</class>
    <class kind="class">harps::compornent::Volume</class>
    <class kind="class">harps::compornent::Wave</class>
    <member kind="function">
      <type>bool</type>
      <name>lu</name>
      <anchorfile>namespaceharps_1_1compornent.html</anchorfile>
      <anchor>52686693ee6e21316ae152459d1263eb</anchor>
      <arglist>(float *_lu, unsigned int *_index)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inverse</name>
      <anchorfile>namespaceharps_1_1compornent.html</anchorfile>
      <anchor>62a13f539cad26886820d23699cd773e</anchor>
      <arglist>(float *_dest, float *_source_orig)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcCoef</name>
      <anchorfile>namespaceharps_1_1compornent.html</anchorfile>
      <anchor>7e2f00e77c2c4b3cab75ccc616740f96</anchor>
      <arglist>(float &amp;_a, float &amp;_b, float _x0, float _y0, float _x1, float _y1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calcCoef</name>
      <anchorfile>namespaceharps_1_1compornent.html</anchorfile>
      <anchor>011aade3968e39a9e933c9bdeb0dac45</anchor>
      <arglist>(float &amp;_a, float &amp;_b, float &amp;_c, float _x0, float _y0, float _x1, float _y1, float _x2, float _y2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>inverse</name>
      <anchorfile>namespaceharps_1_1compornent.html</anchorfile>
      <anchor>b660c352783a5da8d91b8751fc64291b</anchor>
      <arglist>(float *_dest, const float *_source_orig)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Add</name>
    <filename>classharps_1_1compornent_1_1Add.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Add.html</anchorfile>
      <anchor>bd88ad5da1df02fc04751308c81401a9</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Add&lt;  &gt;</name>
    <filename>classharps_1_1compornent_1_1Add_3_01_01_4.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Add_3_01_01_4.html</anchorfile>
      <anchor>567dd3eabdc98493836079278d6065f9</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::BranchByNote</name>
    <filename>classharps_1_1compornent_1_1BranchByNote.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1BranchByNote.html</anchorfile>
      <anchor>e542c236dad37cefaa100c942a3ceae4</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1BranchByNote.html</anchorfile>
      <anchor>ac29b30924a4371c5923c3cdc19f9664</anchor>
      <arglist>(Buffer&lt; float &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1BranchByNote.html</anchorfile>
      <anchor>33a993b8ef0143be5c2a281596a74122</anchor>
      <arglist>(Buffer&lt; double &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Constant</name>
    <filename>classharps_1_1compornent_1_1Constant.html</filename>
    <templarg>_value</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Constant.html</anchorfile>
      <anchor>e4dc4a7527ab078f42ada763db689fd5</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::ConstantMul</name>
    <filename>classharps_1_1compornent_1_1ConstantMul.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>_value</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1ConstantMul.html</anchorfile>
      <anchor>9b7d2a43d400cb3e9378d3c3a661cc69</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Distotion</name>
    <filename>classharps_1_1compornent_1_1Distotion.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>_linear_begin</templarg>
    <templarg>_linear_end</templarg>
    <templarg>_flat_begin</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Distotion.html</anchorfile>
      <anchor>a77b7866fa3aa4951f0c3841bcb26655</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Envelope</name>
    <filename>classharps_1_1compornent_1_1Envelope.html</filename>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_hold</templarg>
    <templarg>_decay</templarg>
    <templarg>_sustain</templarg>
    <templarg>_release</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope.html</anchorfile>
      <anchor>b0f272cb8a1268f8b81979d6b48ce46e</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Envelope&lt; _clock_select, _delay, _attack, _hold, _decay, 0, _release &gt;</name>
    <filename>classharps_1_1compornent_1_1Envelope_3_01__clock__select_00_01__delay_00_01__attack_00_01__hold_396210224e615d03f376f3377e02eb68.html</filename>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_hold</templarg>
    <templarg>_decay</templarg>
    <templarg>_release</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope_3_01__clock__select_00_01__delay_00_01__attack_00_01__hold_396210224e615d03f376f3377e02eb68.html</anchorfile>
      <anchor>50dec6a5f4ad7e503e6a31c57dbe6539</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Envelope2</name>
    <filename>classharps_1_1compornent_1_1Envelope2.html</filename>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_attack_middle</templarg>
    <templarg>_attack_middle_level</templarg>
    <templarg>_hold</templarg>
    <templarg>_hold_level</templarg>
    <templarg>_decay1</templarg>
    <templarg>_decay1_middle</templarg>
    <templarg>_decay1_middle_level</templarg>
    <templarg>_decay1_end_level</templarg>
    <templarg>_decay2</templarg>
    <templarg>_decay2_middle</templarg>
    <templarg>_decay2_middle_level</templarg>
    <templarg>_sustain_level</templarg>
    <templarg>_release</templarg>
    <templarg>_release_middle</templarg>
    <templarg>_release_middle_level</templarg>
    <member kind="typedef">
      <type>Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, _sustain_level, _release, _release_middle, _release_middle_level &gt;</type>
      <name>ThisType</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2.html</anchorfile>
      <anchor>1826d375d377d25e54fdb8a24a519f64</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2.html</anchorfile>
      <anchor>991902e280a18e0d87744d959259f3cc</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initNoteOnEnvelope</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2.html</anchorfile>
      <anchor>f0251b560de2e3a263cd8d0c768293b6</anchor>
      <arglist>(boost::array&lt; float, CACHE_SIZE &gt; &amp;_dest)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initNoteOffEnvelope</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2.html</anchorfile>
      <anchor>e9d3a4889ad359b68b5df6e285626c1e</anchor>
      <arglist>(boost::array&lt; float, CACHE_SIZE &gt; &amp;_dest)</arglist>
    </member>
    <class kind="class">harps::compornent::Envelope2::NoteOff</class>
    <class kind="class">harps::compornent::Envelope2::NoteOn</class>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, 0, _release, _release_middle, _release_middle_level &gt;</name>
    <filename>classharps_1_1compornent_1_1Envelope2_3_01__clock__select_00_01__delay_00_01__attack_00_01__atta211bf396f5638f048319b2d4e63e7d8c.html</filename>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_attack_middle</templarg>
    <templarg>_attack_middle_level</templarg>
    <templarg>_hold</templarg>
    <templarg>_hold_level</templarg>
    <templarg>_decay1</templarg>
    <templarg>_decay1_middle</templarg>
    <templarg>_decay1_middle_level</templarg>
    <templarg>_decay1_end_level</templarg>
    <templarg>_decay2</templarg>
    <templarg>_decay2_middle</templarg>
    <templarg>_decay2_middle_level</templarg>
    <templarg>_release</templarg>
    <templarg>_release_middle</templarg>
    <templarg>_release_middle_level</templarg>
    <member kind="typedef">
      <type>Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, 0, _release, _release_middle, _release_middle_level &gt;</type>
      <name>ThisType</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2_3_01__clock__select_00_01__delay_00_01__attack_00_01__atta211bf396f5638f048319b2d4e63e7d8c.html</anchorfile>
      <anchor>37d98f73a2a68ca59058bc1aa81d5bb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2_3_01__clock__select_00_01__delay_00_01__attack_00_01__atta211bf396f5638f048319b2d4e63e7d8c.html</anchorfile>
      <anchor>410b50ff864375740f3b19cbcc12e624</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initNoteOnEnvelope</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2_3_01__clock__select_00_01__delay_00_01__attack_00_01__atta211bf396f5638f048319b2d4e63e7d8c.html</anchorfile>
      <anchor>2ea5c57e470eef5a9e9f2a56c905d51a</anchor>
      <arglist>(boost::array&lt; float, CACHE_SIZE &gt; &amp;_dest)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initNoteOffEnvelope</name>
      <anchorfile>classharps_1_1compornent_1_1Envelope2_3_01__clock__select_00_01__delay_00_01__attack_00_01__atta211bf396f5638f048319b2d4e63e7d8c.html</anchorfile>
      <anchor>f828999e08175f44767a7a907f1c6e9e</anchor>
      <arglist>(boost::array&lt; float, CACHE_SIZE &gt; &amp;_dest)</arglist>
    </member>
    <class kind="class">harps::compornent::Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, 0, _release, _release_middle, _release_middle_level &gt;::NoteOff</class>
    <class kind="class">harps::compornent::Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, 0, _release, _release_middle, _release_middle_level &gt;::NoteOn</class>
  </compound>
  <compound kind="class">
    <name>harps::compornent::FM</name>
    <filename>classharps_1_1compornent_1_1FM.html</filename>
    <templarg>ModuleType0</templarg>
    <templarg>ModuleType1</templarg>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_hold</templarg>
    <templarg>_decay</templarg>
    <templarg>_sustain</templarg>
    <templarg>_release</templarg>
    <member kind="typedef">
      <type>Mul&lt; Sine&lt; Add&lt; ModuleType0, ModuleType1 &gt; &gt;, Envelope&lt; _clock_select, _delay, _attack, _hold, _decay, _sustain, _release &gt; &gt;</type>
      <name>OperatorType</name>
      <anchorfile>classharps_1_1compornent_1_1FM.html</anchorfile>
      <anchor>886c27da348512aaa4f524a23b57990b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1FM.html</anchorfile>
      <anchor>6705ad0ccfaf5d3f69ebe71f779e3e5f</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::FM&lt; ModuleType0, ModuleType1, 0, 0, 0, 0, 0, 0, 0 &gt;</name>
    <filename>classharps_1_1compornent_1_1FM_3_01ModuleType0_00_01ModuleType1_00_010_00_010_00_010_00_010_00_010_00_010_00_010_01_4.html</filename>
    <templarg>ModuleType0</templarg>
    <templarg>ModuleType1</templarg>
    <member kind="typedef">
      <type>Sine&lt; Add&lt; ModuleType0, ModuleType1 &gt; &gt;</type>
      <name>OperatorType</name>
      <anchorfile>classharps_1_1compornent_1_1FM_3_01ModuleType0_00_01ModuleType1_00_010_00_010_00_010_00_010_00_010_00_010_00_010_01_4.html</anchorfile>
      <anchor>f3ba3681fb3c1359e998c28cceca9474</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1FM_3_01ModuleType0_00_01ModuleType1_00_010_00_010_00_010_00_010_00_010_00_010_00_010_01_4.html</anchorfile>
      <anchor>537f9c217e51240cf7b5215e6b4dbb55</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::FM2</name>
    <filename>classharps_1_1compornent_1_1FM2.html</filename>
    <templarg>ModuleType0</templarg>
    <templarg>ModuleType1</templarg>
    <templarg>_clock_select</templarg>
    <templarg>_delay</templarg>
    <templarg>_attack</templarg>
    <templarg>_attack_middle</templarg>
    <templarg>_attack_middle_level</templarg>
    <templarg>_hold</templarg>
    <templarg>_hold_level</templarg>
    <templarg>_decay1</templarg>
    <templarg>_decay1_middle</templarg>
    <templarg>_decay1_middle_level</templarg>
    <templarg>_decay1_end_level</templarg>
    <templarg>_decay2</templarg>
    <templarg>_decay2_middle</templarg>
    <templarg>_decay2_middle_level</templarg>
    <templarg>_sustain_level</templarg>
    <templarg>_release</templarg>
    <templarg>_release_middle</templarg>
    <templarg>_release_middle_level</templarg>
    <member kind="typedef">
      <type>Volume&lt; Sine&lt; Add&lt; ModuleType0, ModuleType1 &gt; &gt;, Envelope2&lt; _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level, _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level, _decay2, _decay2_middle, _decay2_middle_level, _sustain_level, _release, _release_middle, _release_middle_level &gt; &gt;</type>
      <name>OperatorType</name>
      <anchorfile>classharps_1_1compornent_1_1FM2.html</anchorfile>
      <anchor>2435f01d3a078c2bfea1019d9014e9dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1FM2.html</anchorfile>
      <anchor>3b0e94c69fc8176384827c41fa901ef7</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Generator</name>
    <filename>classharps_1_1compornent_1_1Generator.html</filename>
    <templarg>_clock_select</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Generator.html</anchorfile>
      <anchor>4d3f29a1db7b951848d118dcc34af58d</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Mix</name>
    <filename>classharps_1_1compornent_1_1Mix.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Mix.html</anchorfile>
      <anchor>38faa35f85087729005efa8af7ec0d70</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Mix&lt;  &gt;</name>
    <filename>classharps_1_1compornent_1_1Mix_3_01_01_4.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Mix_3_01_01_4.html</anchorfile>
      <anchor>def174a51cea11929e3c7896e4ccc999</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Mul</name>
    <filename>classharps_1_1compornent_1_1Mul.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Mul.html</anchorfile>
      <anchor>06a25a0fc7e6c36c83ecde2c4bf957dc</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Mul&lt;  &gt;</name>
    <filename>classharps_1_1compornent_1_1Mul_3_01_01_4.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Mul_3_01_01_4.html</anchorfile>
      <anchor>f6a127fc62e00d7436705697f5d15c4a</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::FFT</name>
    <filename>classharps_1_1compornent_1_1FFT.html</filename>
    <templarg>size</templarg>
    <member kind="function">
      <type></type>
      <name>FFT</name>
      <anchorfile>classharps_1_1compornent_1_1FFT.html</anchorfile>
      <anchor>f9e163248a4a1effeb45be7aacf18824</anchor>
      <arglist>(int _inverse)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1FFT.html</anchorfile>
      <anchor>ead57ca53e62bf176a43f9b4c2b356e7</anchor>
      <arglist>(float *_buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1FFT.html</anchorfile>
      <anchor>138cf479685812d1d792d91ab0f40e01</anchor>
      <arglist>(std::complex&lt; float &gt; *_buffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>process</name>
      <anchorfile>classharps_1_1compornent_1_1FFT.html</anchorfile>
      <anchor>dc2aeef5b010a13811af33d2b7fceabf</anchor>
      <arglist>(std::complex&lt; float &gt; *_dest, std::complex&lt; float &gt; *_src, unsigned int _block_size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Noize</name>
    <filename>classharps_1_1compornent_1_1Noize.html</filename>
    <templarg>_lpf</templarg>
    <templarg>_hpf</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Noize.html</anchorfile>
      <anchor>2e28864237d665c259a1e411dd5d7082</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initCache</name>
      <anchorfile>classharps_1_1compornent_1_1Noize.html</anchorfile>
      <anchor>d833603ed1b8e5fec60aa27d8b585160</anchor>
      <arglist>(boost::array&lt; float, CACHE_SIZE &gt; &amp;_dest)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Normalize</name>
    <filename>classharps_1_1compornent_1_1Normalize.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Normalize.html</anchorfile>
      <anchor>19a3130399cf04518ad0be3e987d4bdb</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Rectangle</name>
    <filename>classharps_1_1compornent_1_1Rectangle.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>DutyModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Rectangle.html</anchorfile>
      <anchor>c3c3ccda9f7cb778b24f8038590141f2</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Scale</name>
    <filename>classharps_1_1compornent_1_1Scale.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>_scale</templarg>
    <templarg>_shift</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Scale.html</anchorfile>
      <anchor>8a7d50f85ca482a39fb3920eece71e29</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Scale&lt; ModuleType, 1000, 0 &gt;</name>
    <filename>classharps_1_1compornent_1_1Scale_3_01ModuleType_00_011000_00_010_01_4.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Scale_3_01ModuleType_00_011000_00_010_01_4.html</anchorfile>
      <anchor>5769102734f8ea7c355336550c599220</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Shift</name>
    <filename>classharps_1_1compornent_1_1Shift.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>_shift</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Shift.html</anchorfile>
      <anchor>0593f851fbfe75035df973052f7b4868</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Sine</name>
    <filename>classharps_1_1compornent_1_1Sine.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Sine.html</anchorfile>
      <anchor>9faa8a1827d599007c30037e7f15b56b</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::SwitchingEnvelope</name>
    <filename>classharps_1_1compornent_1_1SwitchingEnvelope.html</filename>
    <templarg>AttackModuleType</templarg>
    <templarg>_attack</templarg>
    <templarg>SustainModuleType</templarg>
    <templarg>ReleaseModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1SwitchingEnvelope.html</anchorfile>
      <anchor>a034bebbc5d41d710d14242499a84203</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Touch</name>
    <filename>classharps_1_1compornent_1_1Touch.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Touch.html</anchorfile>
      <anchor>706224afa2eecdfd994668640d5609c7</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Triangle</name>
    <filename>classharps_1_1compornent_1_1Triangle.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Triangle.html</anchorfile>
      <anchor>48e13276ac76e05e17e3232064152865</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::NES</name>
    <filename>classharps_1_1compornent_1_1NES.html</filename>
    <templarg>ModuleType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1NES.html</anchorfile>
      <anchor>33a4c1c50b22d100ce08925a616058e6</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Volume</name>
    <filename>classharps_1_1compornent_1_1Volume.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>AmpType</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Volume.html</anchorfile>
      <anchor>7268469f57d241e7a8e0bedf98d7a0e8</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::compornent::Wave</name>
    <filename>classharps_1_1compornent_1_1Wave.html</filename>
    <templarg>ModuleType</templarg>
    <templarg>size</templarg>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1compornent_1_1Wave.html</anchorfile>
      <anchor>68ffeef1ee9d0c47e0318f05b4a7089e</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer, CurrentTime &amp;_clock, Note &amp;_note)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const float *</type>
      <name>getWave</name>
      <anchorfile>classharps_1_1compornent_1_1Wave.html</anchorfile>
      <anchor>e43fbb17ad503cbf13ca2a956e148c60</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>harps::input</name>
    <filename>namespaceharps_1_1input.html</filename>
    <class kind="struct">harps::input::Score</class>
    <class kind="class">harps::input::SimpleReader</class>
    <class kind="class">harps::input::Tracks</class>
  </compound>
  <compound kind="struct">
    <name>harps::input::Score</name>
    <filename>structharps_1_1input_1_1Score.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>pos</name>
      <anchorfile>structharps_1_1input_1_1Score.html</anchorfile>
      <anchor>e17864694bc7d1f6c4842919867ad53f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>length</name>
      <anchorfile>structharps_1_1input_1_1Score.html</anchorfile>
      <anchor>3f9a1a8c50a874834877751a8d1dabe5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>note</name>
      <anchorfile>structharps_1_1input_1_1Score.html</anchorfile>
      <anchor>b73ecfe496a3e90669081a968044b78c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>touch</name>
      <anchorfile>structharps_1_1input_1_1Score.html</anchorfile>
      <anchor>49d93f1ba67f1504e5d87e5658a6aad3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::input::SimpleReader</name>
    <filename>classharps_1_1input_1_1SimpleReader.html</filename>
    <templarg>InstrumentType</templarg>
    <member kind="function">
      <type></type>
      <name>SimpleReader</name>
      <anchorfile>classharps_1_1input_1_1SimpleReader.html</anchorfile>
      <anchor>329c834a56b19251d39d127a78f45750</anchor>
      <arglist>(const Score *const _score)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1input_1_1SimpleReader.html</anchorfile>
      <anchor>73abaf1fdf42bcdaa8b2c6ffe0fb5cb7</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEnd</name>
      <anchorfile>classharps_1_1input_1_1SimpleReader.html</anchorfile>
      <anchor>9a4e0775e2fdc12d8ff97352d7e83cce</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>programChange</name>
      <anchorfile>classharps_1_1input_1_1SimpleReader.html</anchorfile>
      <anchor>6223220966d8abe9ecca4a104a02b9a6</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::input::Tracks</name>
    <filename>classharps_1_1input_1_1Tracks.html</filename>
    <templarg>OutputType</templarg>
    <templarg>ReaderType</templarg>
    <templarg>BufferType</templarg>
    <templarg>track_count</templarg>
    <member kind="function">
      <type></type>
      <name>Tracks</name>
      <anchorfile>classharps_1_1input_1_1Tracks.html</anchorfile>
      <anchor>9f4150bcd3a5ac116d4759909ea9a9cd</anchor>
      <arglist>(const char *_sink)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setScore</name>
      <anchorfile>classharps_1_1input_1_1Tracks.html</anchorfile>
      <anchor>194d2399ae3cb04e0c8cf231f03a2265</anchor>
      <arglist>(unsigned int _target, const char *_prog, const harps::input::Score *_score)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1input_1_1Tracks.html</anchorfile>
      <anchor>39bfd26b91c4f04a0c6d9c7fdb01e1d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEnd</name>
      <anchorfile>classharps_1_1input_1_1Tracks.html</anchorfile>
      <anchor>acb1ba476857eeaa4baaaa3e04c549de</anchor>
      <arglist>()</arglist>
    </member>
    <class kind="class">harps::input::Tracks::TrackRunner</class>
  </compound>
  <compound kind="namespace">
    <name>harps::output</name>
    <filename>namespaceharps_1_1output.html</filename>
    <class kind="class">harps::output::ALSA</class>
    <class kind="class">harps::output::Wave</class>
  </compound>
  <compound kind="class">
    <name>harps::output::ALSA</name>
    <filename>classharps_1_1output_1_1ALSA.html</filename>
    <templarg>is_stereo</templarg>
    <templarg>bytes_per_sample</templarg>
    <member kind="function">
      <type></type>
      <name>ALSA</name>
      <anchorfile>classharps_1_1output_1_1ALSA.html</anchorfile>
      <anchor>bd7c14ca3341300700f2f326da1d5395</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ALSA</name>
      <anchorfile>classharps_1_1output_1_1ALSA.html</anchorfile>
      <anchor>6559af972d3a35b4716dde115e154a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1output_1_1ALSA.html</anchorfile>
      <anchor>721e00562d78f619502336705231c930</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>harps::output::Wave</name>
    <filename>classharps_1_1output_1_1Wave.html</filename>
    <templarg>is_stereo</templarg>
    <templarg>bytes_per_sample</templarg>
    <member kind="function">
      <type></type>
      <name>Wave</name>
      <anchorfile>classharps_1_1output_1_1Wave.html</anchorfile>
      <anchor>220425fb4828faccdc2c6f3be63f498c</anchor>
      <arglist>(const char *_filename)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Wave</name>
      <anchorfile>classharps_1_1output_1_1Wave.html</anchorfile>
      <anchor>05c145cb74ff699e183a516a76f9a50a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classharps_1_1output_1_1Wave.html</anchorfile>
      <anchor>88399ca38037a5aa11bd8daa73d91cfa</anchor>
      <arglist>(Buffer&lt; SampleType &gt; &amp;_buffer)</arglist>
    </member>
  </compound>
</tagfile>
